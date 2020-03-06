#include <avr/io.h>
#include <util/delay.h>
#include "nokia5110.h"
#include "joystick.h"
#include "scheduler.h"
#include "timer.h"
#include "bit.h"
#include "screens.h"
#include "PWM.h"
#include "shift.h"

#define button (~PINA & 0x04)
unsigned char max_notes = 8; 
unsigned char notes[8] = {};
unsigned char game_begin;
unsigned char demo_begin;
unsigned char player_begin;
unsigned char curr_round;

unsigned char game_lose;
unsigned char game_win;

unsigned char joy;
unsigned char i;

enum init_state {init1, wait1, start}; init_state;
enum demo_state {init2, wait2, play, blank}; demo_state;
enum play_state {init3, idle, up, down, left, right} play_state;
enum disp_state {init4, display} disp_state;

void tick_init() {
	unsigned char temp = 0x00;
	switch (init_state) { // transitions
		case init1:
			game_begin = 0;
			game_lose = 0;
			game_win = 0;
			player_begin = 0;
			demo_begin = 0;
			curr_round = 0;
			if (!button) {
				init_state = wait1;
			}
			else {
				init_state = init1;
			}
			break;
		case wait1: // add function that creates a random array of 8 numbers between 1-4
			if (button) {
				for (temp = 0; temp < 8; temp++) {
					notes[temp] = (rand() % 4) + 1;
				}
				init_state = start;
				game_begin = 1;
				demo_begin = 1;
				curr_round = 1;
				i = 0;
				PWM_on();
				break;
			}
			else {
				init_state = wait1;
				game_begin = 0;
			}
			break;
		case start:
			if ((game_lose || game_win) && button) {
				play_again_screen();
				init_state = init1;
			}
			else {
				init_state = start;
			}
			break;
	}
	switch (init_state) { // actions
		case init1:
			break;
		case wait1:
			break;
		case start:
			if (game_lose == 1) {
				set_PWM(0);
				PORTD = 0xFF;
				lose_screen();
			}
			else if (game_win == 1) {
				set_PWM(0);
				PORTD = 0xFF;
				win_screen();
			}
			break;
	}
}

void tick_demo () {
	switch(demo_state) {
		case init2:
			if (game_begin && demo_begin) {
				set_PWM(0);
				i = 0;
				demo_state = wait2;
			}
			else {
				demo_state = init2;
			}
			break;
		case wait2:
			if (!player_begin && demo_begin) {
				demo_init();
			}
			if (demo_begin) {
				demo_state = play;
			}
			else {
				demo_state = wait2;
			}
			break;
		case play:
			if (notes[i] == 1) {
				demo_up();
				set_PWM(F4);
				PORTD = 0xF3;
			}
			else if (notes[i] == 2) {
				demo_down();
				set_PWM(C4);
				PORTD = 0xCF;
			}
			else if (notes[i] == 3) {
				demo_left();
				set_PWM(D4);
				PORTD = 0x3F;
			}
			else if (notes[i] == 4) {
				demo_right();
				set_PWM(E4);
				PORTD = 0xFC;
			}
			demo_state = blank;
			i++;
			break;
		case blank:
			demo_init();
			set_PWM(0);
			PORTD = 0xFF;
			if (i < curr_round) { 
				demo_state = play;
			}
			else {
				i = 0;
				demo_state = wait2;
				demo_begin = 0;
				player_begin = 1;
			}
			break;
	}
}

void tick_player() {
	joy = js();
	switch (play_state) {
		case init2:
			if (game_begin && player_begin) {
				play_init();
				play_state = idle;
			}
			else {
				play_state = init2;
			}
			break;
		case idle:
			if (joy == 1) {
				play_state = up;
				set_PWM(F4);
				play_up();
				PORTD = 0xF3;
			}
			else if (joy == 2) {
				play_state = down;
				set_PWM(C4);
				play_down();
				PORTD = 0xCF;
			}
			else if (joy == 3) {
				play_state = left;
				set_PWM(D4);
				play_left();
				PORTD = 0x3F;
			}
			else if (joy == 4) {
				play_state = right;
				set_PWM(E4);
				play_right();
				PORTD = 0xFC;
			}
			else if (i >= max_notes) {
				game_win = 1;
				game_begin = 0;
				play_state = init2;
			}
			else if (i >= curr_round) {
				player_begin = 0;
				demo_begin = 1;
				curr_round++;
				i = 0;
				play_state = init2;
			}
			else {
				play_state = idle;
			}
			break;
		case up:
			if (joy == 1) {
				play_state = up;
				if (notes[i] != 1) {
					game_lose = 1;
					game_begin = 0;
					play_state = init2;
				}
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
				PORTD = 0xFF;
				i++;
			}
			break;
		case down:
			if (joy == 2) {
				play_state = down;
				if (notes[i] != 2) {
					game_lose = 1;
					game_begin = 0;
					play_state = init2;
				}
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
				PORTD = 0xFF;
				i++;
			}
			break;
		case left:
			if (joy == 3) {
				play_state = left;
				if (notes[i] != 3) {
					game_lose = 1;
					game_begin = 0;
					play_state = init2;
				}
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
				PORTD = 0xFF;
				i++;
			}
			break;
		case right:
			if (joy == 4) {
				play_state = right;
				if (notes[i] != 4) {
					game_lose = 1;
					game_begin = 0;
					play_state = init2;
				}
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
				PORTD = 0xFF;
				i++;
			}
			break;
	}
}

void tick_disp() {
	switch (disp_state) { // transitions
		case init4:
			disp_state = display;
			break;
		case display:
			disp_state = display;
			break;
	}
	switch (disp_state) { // actions
		case init4:
			break;
		case display:	
			if (curr_round == 1) {
				transmit_data(0x01);
			}
			else if (curr_round == 2) {
				transmit_data(0x03);
			}
			else if (curr_round == 3) {
				transmit_data(0x07);
			}
			else if (curr_round == 4) {
				transmit_data(0x0F);
			}
			else if (curr_round == 5) {
				transmit_data(0x1F);
			}
			else if (curr_round == 6) {
				transmit_data(0x3F);
			}
			else if (curr_round == 7) {
				transmit_data(0x7F);
			}
			else if (curr_round == 8) {
				transmit_data(0xFF);
			}
			else {
				transmit_data(0x00);
			}
			break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();
	nokia_lcd_init();
	title_screen();
	game_begin = 0;
	PORTD = 0xFF;
	
	static task task1, task2, task3, task4;
	task *tasks[] = { &task1, &task2, &task3, &task4};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = 0;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick_init;
	
	task2.state = 0;
	task2.period = 200;
	task2.elapsedTime = task2.period;
	task2.TickFct = &tick_demo;
	
	task3.state = 0;
	task3.period = 50;
	task3.elapsedTime = task3.period;
	task3.TickFct = &tick_player;
	
	task4.state = 0;
	task4.period = 50;
	task4.elapsedTime = task4.period;
	task4.TickFct = &tick_disp;
	
	TimerSet(1);
	TimerOn();
	
	unsigned short i;
	while (1) {
		for ( i = 0; i < numTasks; i++ ) {
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
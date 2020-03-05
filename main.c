#include <avr/io.h>
#include <util/delay.h>
#include "nokia5110.h"
#include "joystick.h"
#include "scheduler.h"
#include "timer.h"
#include "bit.h"
#include "screens.h"
#include "PWM.h"

#define button (~PINA & 0x04)
unsigned char notes[8] = {1, 2, 3, 4, 1, 2, 3, 4,};
unsigned char game_begin;
unsigned char demo_begin;
unsigned char player_begin;
unsigned char joy;
unsigned char i;

enum init_state {init1, wait1, start}; init_state;
enum demo_state {init2, wait2, play, blank}; demo_state;
enum play_state {init3, idle, up, down, left, right} play_state;

void tick_init() {
	switch (init_state) {
		case init1:
			game_begin = 0;
			player_begin = 0;
			demo_begin = 0;
			title_screen();
			PORTC = 0xFF;
			init_state = wait1;
			break;
		case wait1: // add function that creates a random array of 8 numbers between 1-4
			if (button) {
				init_state = start;
				game_begin = 1;
				demo_begin = 1;
				break;
			}
			else {
				init_state = wait1;
				game_begin = 0;
			}
			break;
		case start:
			break;
	}
}

void tick_demo () {
	switch(demo_state) {
		case init2:
			if (game_begin && demo_begin) {
				demo_state = wait2;
			}
			else {
				demo_state = init2;
			}
			break;
		case wait2:
			demo_init();
			break;
		case play:
			break;
		case blank:
			break;
	}
}

void tick_player() {
	joy = js();
	switch (play_state) {
		case init2:
			if (game_begin && player_begin) {
				play_init();
				PWM_on();
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
				PORTC = 0x00;
			}
			else if (joy == 2) {
				play_state = down;
				set_PWM(C4);
				play_down();
			}
			else if (joy == 3) {
				play_state = left;
				set_PWM(D4);
				play_left();
			}
			else if (joy == 4) {
				play_state = right;
				set_PWM(E4);
				play_right();
			}
			else {
				play_state = idle;
			}
			break;
		case up:
			if (joy == 1) {
				play_state = up;
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
				PORTC = 0xFF;
			}
			break;
		case down:
			if (joy == 2) {
				play_state = down;
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
			}
			break;
		case left:
			if (joy == 3) {
				play_state = left;
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
			}
			break;
		case right:
			if (joy == 4) {
				play_state = right;
			}
			else {
				play_state = idle;
				play_init();
				set_PWM(0);
			}
			break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	ADC_init();
	nokia_lcd_init();
	nokia_lcd_clear();
	game_begin = 0;
	
	static task task1, task2, task3;
	task *tasks[] = { &task1, &task2, &task3};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = 0;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick_init;
	
	task2.state = 0;
	task2.period = 700;
	task2.elapsedTime = task2.period;
	task2.TickFct = &tick_demo;
	
	task3.state = 0;
	task3.period = 50;
	task3.elapsedTime = task3.period;
	task3.TickFct = &tick_player;
	
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
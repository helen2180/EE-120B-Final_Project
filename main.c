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
unsigned char joy;

enum joy_state {start, idle, up, down, left, right} joy_state;

void tick_js() {
	joy = js();
	switch (joy_state) {
		case start:
			if (button) {
				play_init();
				PWM_on();
				joy_state = idle;
			}
			else {
				joy_state = start;
			}
			break;
		case idle:
			if (joy == 1) {
				joy_state = up;
				set_PWM(F4);
				play_up();
			}
			else if (joy == 2) {
				joy_state = down;
				set_PWM(C4);
				play_down();
			}
			else if (joy == 3) {
				joy_state = left;
				set_PWM(D4);
				play_left();
			}
			else if (joy == 4) {
				joy_state = right;
				set_PWM(E4);
				play_right();
			}
			else {
				joy_state = idle;
			}
			break;
		case up:
			if (joy == 1) {
				joy_state = up;
			}
			else {
				joy_state = idle;
				play_init();
				set_PWM(0);
			}
			break;
		case down:
			if (joy == 2) {
				joy_state = down;
			}
			else {
				joy_state = idle;
				play_init();
				set_PWM(0);
			}
			break;
		case left:
			if (joy == 3) {
				joy_state = left;
			}
			else {
				joy_state = idle;
				play_init();
				set_PWM(0);
			}
			break;
		case right:
			if (joy == 4) {
				joy_state = right;
			}
			else {
				joy_state = idle;
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
	DDRD = 0xFF; PORTD = 0x00;

	ADC_init();
	LCD_init();
	nokia_lcd_init();
	nokia_lcd_clear();
	
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = 0;
	task1.period = 5;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick_js;
	
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
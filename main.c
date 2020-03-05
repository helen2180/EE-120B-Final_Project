#include <avr/io.h>
#include <util/delay.h>

#include "nokia5110.h"
#include "io.h"
#include "joystick.h"

// Nokia 5110 screen functions
void title_screen() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(20, 0);
	nokia_lcd_write_string("Just", 2);
	nokia_lcd_set_cursor(15, 15);
	nokia_lcd_write_string("Dance", 2);
	nokia_lcd_set_cursor(12, 35);
	nokia_lcd_write_string("Revolution", 1);
	nokia_lcd_render();
}
		
void demo_init() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_render();
}
		
void demo_up() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(28, 20);
	nokia_lcd_write_string("Up", 3);
	nokia_lcd_render();
}
		
void demo_down() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Down", 3);
	nokia_lcd_render();
}
		
void demo_left() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Left", 3);
	nokia_lcd_render();
}
		
void demo_right() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(1, 5);
	nokia_lcd_write_string("Remember this:", 1);
	nokia_lcd_set_cursor(2, 20);
	nokia_lcd_write_string("Right", 3);
	nokia_lcd_render();
}

void play_init() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_render();
}

void play_up() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(28, 20);
	nokia_lcd_write_string("Up", 3);
	nokia_lcd_render();
}
		
void play_down() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Down", 3);
	nokia_lcd_render();
}
		
void play_left() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(10, 20);
	nokia_lcd_write_string("Left", 3);
	nokia_lcd_render();
}
		
void play_right() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(13, 5);
	nokia_lcd_write_string("Your Turn:", 1);
	nokia_lcd_set_cursor(2, 20);
	nokia_lcd_write_string("Right", 3);
	nokia_lcd_render();
}
		
void game_over_screen () {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(20, 5);
	nokia_lcd_write_string("Game", 2);
	nokia_lcd_set_cursor(20, 25);
	nokia_lcd_write_string("Over", 2);
	nokia_lcd_render();
}
		
void win_screen () {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(27, 5);
	nokia_lcd_write_string("You", 2);
	nokia_lcd_set_cursor(24, 25);
	nokia_lcd_write_string("Win!", 2);
	nokia_lcd_render();
}

void play_again_screen() {
	nokia_lcd_clear();
	nokia_lcd_set_cursor(20, 5);
	nokia_lcd_write_string("Play", 2);
	nokia_lcd_set_cursor(10, 25);
	nokia_lcd_write_string("Again?", 2);
	nokia_lcd_render();
}

#define button (~PINA & 0x04)
unsigned char joy;
enum joy_state {start, idle, up, down, left, right} joy_state;

void tick_js() {
	joy = js();
	switch (joy_state) {
		case start:
			if (button) {
				play_init();
				joy_state = idle;
			}
			else {
				joy_state = start;
			}
			break;
		case idle:
			if (joy == 1) {
				joy_state = up;
				play_up();
			}
			else if (joy == 2) {
				joy_state = down;
				play_down();
			}
			else if (joy == 3) {
				joy_state = left;
				play_left();
			}
			else if (joy == 4) {
				joy_state = right;
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
			}
			break;
		case down:
			if (joy == 2) {
				joy_state = down;
			}
			else {
				joy_state = idle;
				play_init();
			}
			break;
		case left:
			if (joy == 3) {
				joy_state = left;
			}
			else {
				joy_state = idle;
				play_init();
			}
			break;
		case right:
			if (joy == 4) {
				joy_state = right;
			}
			else {
				joy_state = idle;
				play_init();
			}
			break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	ADC_init();
	LCD_init();
	nokia_lcd_init();
	nokia_lcd_clear();
	
	while (1) {
		tick_js();
	}
}
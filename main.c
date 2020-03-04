#include <avr/io.h>
#include <util/delay.h>

#include "nokia5110.h"
#include "io.h"
#include "joystick.h"

unsigned char joy;
enum state {idle, up, down, left, right} state;

void tick_js() {
	joy = js();
	switch (state) {
		case idle:
		if (joy == 1) {
			LCD_ClearScreen();
			LCD_DisplayString(1, "Up");
			nokia_lcd_set_cursor(22, 0);
			nokia_lcd_write_string("Weather", 1);
			nokia_lcd_set_cursor(15, 12);
			nokia_lcd_write_string("Sunny", 2);
			nokia_lcd_set_cursor(0, 30);
			nokia_lcd_write_string("Enjoy a warm  and sunny day!", 1);
			nokia_lcd_render();
			state = up;
		}
		else if (joy == 2) {
			LCD_ClearScreen();
			LCD_DisplayString(1, "Down");
			nokia_lcd_set_cursor(22, 0);
			nokia_lcd_write_string("Weather", 1);
			nokia_lcd_set_cursor(15, 12);
			nokia_lcd_write_string("Rainy", 2);
			nokia_lcd_set_cursor(10, 30);
			nokia_lcd_write_string("Remember to", 1);
			nokia_lcd_set_cursor(15, 38);
			nokia_lcd_write_string("stay dry!", 1);
			nokia_lcd_render();
			state = down;
		}
		else if (joy == 3) {
			LCD_ClearScreen();
			LCD_DisplayString(1, "Left");
			nokia_lcd_set_cursor(22, 0);
			nokia_lcd_write_string("Weather", 1);
			nokia_lcd_set_cursor(10, 12);
			nokia_lcd_write_string("Cloudy", 2);
			nokia_lcd_set_cursor(10, 30);
			nokia_lcd_write_string("Remember to", 1);
			nokia_lcd_set_cursor(5, 38);
			nokia_lcd_write_string("dress warmly!", 1);
			nokia_lcd_render();
			state = left;
		}
		else if (joy == 4) {
			LCD_ClearScreen();
			LCD_DisplayString(1, "Right");
			state = right;
		}
		else {
			state = idle;
		}
		break;
		case up:
		if (joy == 1) {
			state = up;
		}
		else {
			state = idle;
			LCD_ClearScreen();
			nokia_lcd_clear();
		}
		break;
		case down:
		if (joy == 2) {
			state = down;
		}
		else {
			state = idle;
			LCD_ClearScreen();
			nokia_lcd_clear();
		}
		break;
		case left:
		if (joy == 3) {
			state = left;
		}
		else {
			state = idle;
			LCD_ClearScreen();
			nokia_lcd_clear();
		}
		break;
		case right:
		if (joy == 4) {
			state = right;
		}
		else {
			state = idle;
			LCD_ClearScreen();
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
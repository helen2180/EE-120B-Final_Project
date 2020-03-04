#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "io.h"
#include "joystick.h"

#define button (~PINA & 0x04)
#define reset (~PINA & 0x08)

// button is also the dig button

enum state {wait, press} state;

unsigned char x;
unsigned char i;
unsigned char temp = 0x00;

void tick() {
	switch (state) { //transitions
		case wait:
			if (button) {
				state = press;
				for (i = 0; i < 4; i++) {
					x = rand() % 2;
					temp = temp | (x << i);
				}
			}
			else {
				state = wait;
			}
			break;
		case press:
			if (button) {
				state = press;
			}
			else {
				state = wait;
				temp = 0;
			}
			break;
	}
}

int main(void) {
  DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

  srand(time(0));

	unsigned char joy;

	ADC_init();
	LCD_init();

  while (1) {
    tick();
	  joy = js();
    if (joy == 1) {
      LCD_ClearScreen();
    	LCD_DisplayString(1, "Up");
    }
    else if (joy == 2) {
  		LCD_ClearScreen();
    	LCD_DisplayString(1, "Down");
    }
  	else if (joy == 3) {
    	LCD_ClearScreen();
    	LCD_DisplayString(1, "Left");
    }
    else if (joy == 4) {
    	LCD_ClearScreen();
    	LCD_DisplayString(1, "Right");
    }
  }
}

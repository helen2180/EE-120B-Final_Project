#include <avr/io.h>
#include "io.h"
#include "joystick.h"

#define dig (~PINA & 0x04)
#define reset (~PINA & 0x08)


int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char joy;
	
	ADC_init();
	LCD_init();
	
    while (1) {
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
		
		if (dig) {
			PORTB = 0x01;
		}
		if (reset) {
			PORTB = 0x02;
		}
    }
}


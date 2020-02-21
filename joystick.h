#ifndef JOYSTICK_H_
#define JOYSTICK_H_

void ADC_init(){
	ADMUX = (1<<REFS0);
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

unsigned short ReadADC(unsigned char ch){
	ch = ch & 0x07;
	ADMUX = (ADMUX & 0xF8) | ch;
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	return(ADC);
}

unsigned short x;
unsigned short y;

int js(void){
	x = ReadADC(0);
	y = ReadADC(1);
	if(x > 750){
		return 4;
	}
	else if(x < 350){
		return 3;
	}
	else if(y > 750 ){
		return 2;
	}
	else if(y < 350){
		return 1;
	}
	else{
		return 0;
	}
}


#endif /* JOYSTICK_H_ */
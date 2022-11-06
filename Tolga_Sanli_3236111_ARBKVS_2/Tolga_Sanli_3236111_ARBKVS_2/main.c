/*
 * Tolga_Sanli_3236111_ARBKVS_2.c
 *
 * Created: 28.10.2022 09:27:35
 * Author : TolgaSanli
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL //CPU hat eine Taktfrequenz von 16.000.000 Hertz
#include <util/delay.h>

#define led0 PINB0
#define led9 PINB1
#define sw0 PIND2
#define sw1 PIND3
int blinkstatus = 1;
int aktuellerLED = PINB0;
int zustandDauerlicht = 1;

int main(void)
{
	
	DDRB = 0xff;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0xff;
	
	
	
	while (1)
	{
		blinkmodus();
		// &= binary and -> löschen die bits(?)
		// |= binary or -> Wir setzen den Bit
		// ^ exclusive or -> bit toggeln
		// >> rotate right
		// << rotate left
		// ~ Bit invertierten
		if(blinkstatus == 1)
		{
			PORTB &= ~(1<< (!aktuellerLED)); // 0000 0001 & 1111 1110
			PORTB ^= (1 << aktuellerLED);	 // 0000 0001 xor 1111 1110 = 1111 1111
		}
		else
		{
			PORTB &= ~(1<< (!aktuellerLED));
			PORTB |= (1 << aktuellerLED);
		}
		_delay_ms(250);
	}
}

void blinkmodus(){
	if(!(PIND & (1<<sw0)))
	{
		if(aktuellerLED == led0){
			if(blinkstatus == 1)
			{
				blinkstatus = 0;
			}
			else
			{
				blinkstatus = 1;
			}
		}else{
			aktuellerLED = led0;
		}	
	}
	if(!(PIND & (1<<sw1)))
	{
		if(aktuellerLED == led9){
			if(blinkstatus == 1){
				blinkstatus = 0;
			}
			else
			{
				blinkstatus = 1;
			}
		}else{
			aktuellerLED = led9;
		}	
	}
}

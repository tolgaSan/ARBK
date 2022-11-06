/*
 * Tolga_Sanli_3236111_ARBKVS_2_interrupt.c
 *
 * Created: 06.11.2022 19:48:21
 * Author : TolgaSanli
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL //CPU hat eine Taktfrequenz von 16.000.000 Hertz
#include <util/delay.h>
#include <avr/interrupt.h>

#define led0 PINB0
#define led9 PINB1
#define sw0 PIND2
#define sw1 PIND3
int blinkstatus = 1;
int aktuellerLED = PINB0;
int zustandDauerlicht = 1;

//ISR erklären können
//Interrupt Service Routine speichert beim Interrupt Daten ins Register, führt das Interrupt aus, gibt die Daten am ende zurück
ISR(INT0_vect){
	if(aktuellerLED == led0){
		//If else Bedingung um Blinkstatus abzuändern (Blinken oder Dauerleuchten)
		if(blinkstatus == 1)
		{
			blinkstatus = 0;
		}
		else
		{
			blinkstatus = 1;
		}
		}else{
		//Bei Knopfdruck SW0 bleibt der aktuell leuchtende LED bei D0
		aktuellerLED = led0;
	}
}

ISR(INT1_vect){
	if(aktuellerLED == led9){
		//Blinkstatus ändern
		if(blinkstatus == 1){
			blinkstatus = 0;
		}
		else
		{
			blinkstatus = 1;
		}
		}else{
		//aktuelleerLED ändern, falls aktuellerLED ungleich led9
		aktuellerLED = led9;
	}
}

int main(void)
{
	
	//Eingänge und Ausgänge definiert
	DDRB = 0xff;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0xff;
	
	//External Interrupt Control Register A
	//externer PIN (INT0/1) aktiviert den interrupt 
	//VALUE11 steigender Flanke generiert einen Interruptanfrage
	//VALUE01 Irgendeine logische Änderung an INT0 oder INT1 generiert ein interrupt request
	EICRA |= (1<<ISC11) | (1<<ISC01);
	
	//External Interrupt Mask Register
	//aktiviert den Interrupt 0 und 1 (BZW. Stecker)
	EIMSK |= (1<<INT0);
	EIMSK |= (1<<INT1);
	//Erlaubt Interrupts?
	sei();
	
	while (1)
	{
		//blinkmodus();
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


/*
void blinkmodus(){
	//wenn Taste sw0 gedrückt wird, dann if ausführen
	//Negation, da der Schalter lowactive ist
	if(!(PIND & (1<<sw0)))
	{
		//aktuellerLED gleich led0 (PINB0 bzw D0)
		if(aktuellerLED == led0){
			//If else Bedingung um Blinkstatus abzuändern (Blinken oder Dauerleuchten)
			if(blinkstatus == 1)
			{
				blinkstatus = 0;
			}
			else
			{
				blinkstatus = 1;
			}
			}else{
			//Bei Knopfdruck SW0 bleibt der aktuell leuchtende LED bei D0
			aktuellerLED = led0;
		}
	}
	//wenn Taste sw1 gedrückt wird, dann if ausführen
	if(!(PIND & (1<<sw1)))
	{
		//aktuellerLED gleich led9 (PINB1 bzw D9)
		if(aktuellerLED == led9){
			//Blinkstatus ändern
			if(blinkstatus == 1){
				blinkstatus = 0;
			}
			else
			{
				blinkstatus = 1;
			}
			}else{
				//aktuelleerLED ändern, falls aktuellerLED ungleich led9
			aktuellerLED = led9;
		}
	}
}
*/
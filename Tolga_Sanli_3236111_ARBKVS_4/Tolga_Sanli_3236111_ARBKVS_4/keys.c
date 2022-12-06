/*
 * keys.c
 *
 * Created: 24.11.2022 14:46:57
 *  Author: TolgaSanli
 */ 
#include "keys.h"

void ports()
{

	DDRD = 0xff;	//DDRD Ausg�nge f�r die LED a-g
	PORTD = 0x00;		// = 0 
	DDRB = 0x01;	//PINB als Eingang f�r A: wird gebraucht f�r INT
	PORTB = (1<< PINB1); // f�r SW1
	DDRC = 0x00; //DDRC alles Eing�nge
	PORTC = (1<< PINC1); //F�r SW2 f�r PCINT belegen
	cli(); //Interrupt deaktivieren
	
	//Timergeschichte siehe Pr. 3
	PCICR = 0x03;			//Bit an 1. und 2. Stelle schaltet PB und PC
	PCMSK0 = (1<< PINB1);	//Aktiviere PCINT auf PB1
	PCMSK1 = (1<< PINC1);	//Aktiviere PCINT auf PC1
	TCCR1B = (1 << CS11) | (1 << CS10) | (1<< WGM12);	//Timergeschichte siehe Pr. 3
	TIMSK1 = (1 << OCIE1A);								//Timergeschichte siehe Pr. 3
	OCR1A = 249;
	
	/*
	kurze Wdh. zu Timer:  TCCR1B mit CS11 und CS10 Verteiler/Prescaler auf 64 bestimmt. 
	TIMSK: Timer Overflow Interrupt freischalten. Mit 1 auf OCIE1A haben wir einen Vergleichswert d.h. Interrupt
	wird bei Vergleichswert aktiviert
	OCR1A ist der Z�hler f�r TIMSK bzw OCIE1A um abzugleichen
	*/
	
	
	sei(); //Interrupt aktivieren
}
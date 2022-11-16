/*
 * Tolga_Sanli_3236111_ARBKVS_3.c
 *
 * Created: 15.11.2022 11:12:49
 * Author : TolgaSanli
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL //CPU hat eine Taktfrequenz von 16.000.000 Hertz
#include <util/delay.h>
#include <avr/interrupt.h>

//Compliler darf die Variable nicht optimieren 
//Variable wird im RAM gespeichert anstatt im Register, RAM-genauer Register 
//Es darf nicht außerhalb vom Verwendungsort benutzt werden. 
volatile uint32_t zaehler = 0;


ISR(TIMER1_COMPA_vect)
{
	zaehler++;
}

void waitfor(uint32_t x)
{
	uint32_t waittill = zaehler + x;
	if (waittill <= 4294967295)
	{
		while(waittill > zaehler)
		{
			//do nothing
		}
	}
}

void waituntil(uint32_t x)
{
	if (x <= 4294967295)
	{
		while(zaehler < x)
		{
			//do nothing
		}
	}
}

int main()
{
	//Die 1 bei Befehle sagt aus, welcher Bittimer das ist. 1 = 16 Bit-Timer
	//D0 led als output (eigentlich alle D als output)
	DDRD = 0xff; 
	PORTD = 0x00;
	
	//TCNT -> Overflow value
	//Timer/Counter Control Register B 
	//3 Bits im Register (CA12, CA11, CS10)
	//0 0 0 -> no clock source (Timer stopped)
	//0 0 1 -> /1 no prescaling
	//0 1 0 -> /8 prescaler
	//0 1 1 -> /64From prescaler
	//1 0 0 -> /256 From prescaler
	//1 0 1 -> /1024 From prescaler
	//1 1 0 -> External clock source on T1 pin. Clock on falling edge
	//1 1 1 -> External clock source on T1 pin. Clock on rising edge 
	//hierbei CS11 => 1 | WGM12 => 1
	//CS11 = sets the prescaler to 64 i think
	//WGM12 = WGM12 daher, weil wir einen Vergleichswert haben können. D.h. Vergleichswert kommt an, Datenregister wieder auf 0, 
	//16mio HZ * (ms/prescale) = 250 takt dauert 1 ms
	TCCR1B = (1 << CS11) | (1 << CS10) | (1<< WGM12);	
	//Timer/Counter Interrupt Mask -> OCIE1A bekommt den Wert 1, da hierbei zusätzlich einen Vergleichswert zum Überlauf definiert wird
	//Beim Vergleichswert wird ein Interrupt ausgelöst d.h. unsere Variabel zaehler inkrementiert = 1 Inkement -> 1ms 
	TIMSK1 = (1 << OCIE1A);	
	//Unser Vergleichswert (250), fängt von 0 an zu zählen, daher 250-1
	OCR1A = 249;
	sei();
	
	while(1)
	{
		//waituntil(2000);
		//PORTD |= (1<<PIND0);
		//waituntil(4000);
		//PORTD = 0b00000000;
		
		//waitfor(500);
		PORTD ^= (1<<PIND0);
		waituntil(1000);
		
		PORTD ^= (1<<PIND0);
		waituntil(2000);
		
		PORTD ^= (1<<PIND0);
		waituntil(3000);
	}
}

/*
 * sevenseg.c
 *
 * Created: 24.11.2022 14:47:40
 *  Author: TolgaSanli
 */ 

#include "sevenseg.h"

volatile uint32_t zaehler = 0;
//Timergeschichte siehe Pr.3
ISR(TIMER1_COMPA_vect)
{
	zaehler++;
}

void waitfor(uint32_t x)
{
	uint32_t waittill = zaehler + x;
	if (waittill <= 2^32)
	{
		while(waittill > zaehler)
		{
			//do nothing
		}
	}
}

void display(int x)
{
	PORTD = x;
	waitfor(10); //waitfor 10 lässt es wirken, als würde LED1 und LED2 dauerhaft blinken, ab ~15 sieht man es schnell blinken
	PORTB ^= (1 << PINB0);
}
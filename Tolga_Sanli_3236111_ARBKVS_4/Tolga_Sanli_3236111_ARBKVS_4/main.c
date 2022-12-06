/*
 *  Author: TolgaSanli 
 */ 


#include "sevenseg.h"
#include "keys.h"
volatile uint32_t zahl = 0;

ISR(PCINT0_vect)
{
	if (!(PINB & (1<<PINB1)))
	{
		if (zahl == 0)
		{
			zahl = 100;
		}

		zahl--;
	}
}

ISR(PCINT1_vect)
{
	if (!(PINC & (1<<PINC1)))
	{
		if (zahl == 99)
		{
			zahl = -1;
		}
		zahl++;
		
	}
}


int main(void)
{
    ports();           
	unsigned int zahlen[10]={
		64,   // 0 
		121,  // 1
 		36,   // 2
		48,   // 3 
		25,   // 4
		18,   // 5
		2,    // 6
		120,  // 7
		0,    // 8
		16    // 9
		};
	
    while (1) 
    {
		display(zahlen[zahl%10]);
		display(zahlen[zahl/10]);
    }
}


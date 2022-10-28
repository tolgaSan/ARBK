/*
 * Tolga_Sanli_3236111_ARBKVS_2.c
 *
 * Created: 28.10.2022 09:27:35
 * Author : TolgaSanli
 */ 
#define F_CPU 16000000UL //CPU hat eine Taktfrequenz von 16.000.000 Hertz
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//Pin Eingänge und Ausgänge
	//Alle Ports als Eingang, da alles auf 1
	DDRD = 0x03;
	//PORTD = ausgang definieren. Bzw. setzen
	PORTD = 0b00000000;
    //unendlicher loop
    while (1) 
    {
		// &= binary and -> löschen die bits(?)
		// |= binary or -> Wir setzen den Bit
		// ^ exclusive or -> bit toggeln
		// >> rotate right
		// << rotate left
		// ~ Bit invertierten
		PORTD |= (1<<0); 
	
		//PORTD &= (1<<1);
		_delay_ms(1000);
 		PORTD &= (1<<1); // !0b00000001 AND 0b11111110 << eins setzen -> 0b00000001 ????????
		_delay_ms(1000);
		
// 		PORTD |= (1<<1);
// 		//_delay_ms(1000);
// 		PORTD &= (1<<2); // !0b00000001 AND 0b11111110 << eins setzen -> 0b00000001 ????????
// 		//_delay_ms(1000);
    }
}


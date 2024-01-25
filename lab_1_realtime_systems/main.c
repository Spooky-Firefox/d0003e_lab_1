/*
 * lab_1_realtime_systems.c
 *
 * Created: 2024-01-22 09:59:33
 * Author : oller
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"
#include "primes.h"


static uint16_t counter_plus_0_5_sec;

void setupTIMER(){
		// use the 8 MHz system clock
		// prescaler 256
		// clkio/256 = 0b100 = 0x4
		TCCR1B = 0x4 << CS10;
}

uint16_t read_counter(){
	// reading lower bit, saves higer bit to tmp
	uint8_t lower = TCNT1L;
	// reading higer bit from tmp
	uint8_t higer = TCNT1H;
	return ((uint16_t)higer<<8) | (uint16_t)lower;
}

uint8_t passed_0_5_sec(){
	
}

int main(void)
{	
	setupTIMER();
	setupLCD();
	
	while (1)
	{
		if (passed_0_5_sec()){
			toggle_s1();
		}
		writeLong(prime);
		next_prime();
		for (uint8_t i = 0; i<40; i++)
		{
			_delay_ms(100);
		}
	}
}


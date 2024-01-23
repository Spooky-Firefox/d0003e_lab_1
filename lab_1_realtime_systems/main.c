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

int is_prime(long i){
	long n = 2;
	while(n < i){
		if (i % n == 0){
			return 0;
		}
		n++;
	}
	return 1;
}

void primes(){
	long val = 2;
	while(val < 100001){
		if(is_prime(val) == 1){
			// print to screen
			writeLong(val);
		}
		val = val + 1;
	}
}

void write_to_counter(uint16_t val){
	// writing the high byte to tmp
	TCNT1H = (uint8_t)(val>>8);
	// writing the low bytes to lower, causeing temp to become higher;
	TCNT1L = (uint8_t)val;
}

void write_to_timer_compare(uint16_t val){
	OCR1A = val;
}
int main(void)
{	
	setupLCD();
	primes();
	while (1)
	{
		toogle_s1();
		for (uint8_t i = 0; i<40; i++)
		{
			_delay_ms(100);
		}
	}
}


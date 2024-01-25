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

// clock 8MHz
// prescaler 1024
// inc 8MHz/256 = 31250Hz
// 0.5s*31250(1/s) = 15625
#define DELAY_0_5_SEC 15625


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



uint16_t next_count_value;
uint16_t prevues_count_value;

uint8_t passed_0_5_sec(){
	uint16_t cur = read_counter();
	// special case overflow
	if (prevues_count_value > next_count_value){
		if (cur > next_count_value && cur < prevues_count_value){
			prevues_count_value = next_count_value;
			next_count_value = next_count_value + DELAY_0_5_SEC;
			return 1;
		} 
		else {
			return 0;
		}
	}
	else if (cur > next_count_value || cur < prevues_count_value){
		prevues_count_value = next_count_value;
		next_count_value = next_count_value + DELAY_0_5_SEC;
		return 1;
	} 
	else {
		return 0;
	}
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
	}
}


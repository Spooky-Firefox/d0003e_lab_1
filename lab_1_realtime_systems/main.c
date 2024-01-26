/*
 * lab_1_realtime_systems.c
 *
 * Created: 2024-01-22 09:59:33
 * Author : oller
 */ 
 

#include <avr/io.h>
#include <stdint.h>
#include "lcd.h"
#include "primes.h"
#include "timer.h"

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


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
#include "joy_stick.h"

int main(void){	
	setupTIMER();
	setupLCD();
	setupJOYSTICK();
	toggle_s4();

	while (1)
	{
		if (passed_0_5_sec()){
			toggle_s1();
		}
		if (joy_release()){
			toggle_s4();
			toggle_s9();
		}
		writeLong(prime);
		next_prime();
	}
}

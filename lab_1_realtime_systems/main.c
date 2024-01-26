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

// joystick press is on portB bit 5
// 0x0001_0000 = 0x40
#define JOY_PRESS_MASK 0x10
#define JOY_PRESS_BIT 4

void setupJOYSTICK(){
	// configure the controll register

	// set to input, DDRB bit 7 zero
	// set the pull up resistor PORTB bit 7 one
	PORTB = PINB | (1<<JOY_PRESS_BIT);
	// PORTB = 0xff;
}

// returns true if joystick is down false if not
uint8_t is_joistick_down(){
	return (PINB & JOY_PRESS_MASK) != JOY_PRESS_MASK;
}


uint8_t last_joy_state = 0;
uint8_t joy_release(){
	// swaps the toggles of s3 and s4 button goes from pressed to not pressed
	if (is_joistick_down() == 0 && last_joy_state == 1){
		last_joy_state = is_joistick_down();
		return 1;
	}
	last_joy_state = is_joistick_down();
	return 0;
}

int main(void)
{	
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


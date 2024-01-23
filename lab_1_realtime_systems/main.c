/*
 * lab_1_realtime_systems.c
 *
 * Created: 2024-01-22 09:59:33
 * Author : oller
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


// the display codes for 0 to 9 in scc format
static uint16_t numbers[] = {
	//hex	  mpnd_legc_jfhb_k--a
	0x1551,	//0001_0101_0101_0001   0
	0x0110,	//0000_0001_0001_0000   1
	0x1e11,	//0001_1110_0001_0001   2
	0x1911,	//0001_1001_0001_0001   3
	0x0b50,	//0000_1011_0101_0000   4
	0x1b41,	//0001_1011_0100_0001   5
	0x1f41,	//0001_1111_0100_0001   6
	0x0111,	//0000_0001_0001_0001   7
	0x1f51,	//0001_1111_0101_0001   8
	0x1b51	//0001_1011_0101_0001   9
};

// a struct to hold the segment values of a digit
struct digit_reg {
	uint8_t x0;
	uint8_t x5;
	uint8_t x10;
	uint8_t x15;
};


// note return the position of the char at the left position
struct digit_reg scc_to_digit_reg(uint16_t scc){
	struct digit_reg out = {0,0,0,0};
	out.x0 = (uint8_t)(scc & 0x000f);
	out.x5 = (uint8_t)((scc & 0x00f0) >> 4);
	out.x10 = (uint8_t)((scc & 0x0f00) >> 8);
	out.x15 = (uint8_t)((scc & 0xf000) >> 12);
	return out;
}

// converts a digit_reg struct to have char at right by shifting the bits
void digit_reg_to_right(struct digit_reg *digit_reg){
	digit_reg->x0 = digit_reg->x0 << 4;
	digit_reg->x5 = digit_reg->x5 << 4;
	digit_reg->x10 = digit_reg->x10 << 4;
	digit_reg->x15 = digit_reg->x15 << 4;
}

void setupLCD(){
	// lcd control reg a
	// lcd enable
	// lcd low power waveform
	LCDCRA = (1<<LCDEN) | (1<<LCDAB);
	// lcd control reg b
	// external clock
	// lcd mux 11, 1/4 duty
	LCDCRB = (1<<LCDCS) | (0x3<<LCDMUX0);
	// lcd frame rate register
	// clock divider 8 0x7=0b111
	LCDFRR = (0x7<<LCDCD0);
	// lcd contrast control register
	// lcd voltage 3.35 0xf = 0b1111
	LCDCCR = (0xf<<LCDCC0);
}

// writes a char over current segments by using or on the registers
void write_over_digit_reg(volatile uint8_t* reg_ptr, struct digit_reg *digit){
	*reg_ptr = *reg_ptr | digit->x0;
	*(reg_ptr+5) = *(reg_ptr+5) | digit->x5;
	*(reg_ptr+10) = *(reg_ptr+10) | digit->x10;
	*(reg_ptr+15) = *(reg_ptr+15) | digit->x15;
}

// and the relevant digit register with the mask, useful for clearing digits
void and_digit_reg(volatile uint8_t* reg_ptr, uint8_t mask){
	*reg_ptr = *reg_ptr & mask;
	*(reg_ptr+5) = *(reg_ptr+5) & mask;
	*(reg_ptr+10) = *(reg_ptr+10) & mask;
	*(reg_ptr+15) = *(reg_ptr+15) & mask;
}

int main(void)
{	
	setupLCD();


    /* Replace with your application code */
    while (1) 
    {
		for(uint8_t i = 0;i<10;i++) {
			struct digit_reg tmp = scc_to_digit_reg(numbers[i]);
			digit_reg_to_right(&tmp);
			and_digit_reg(&LCDDR0, 0x00);
			write_over_digit_reg(&LCDDR0, &tmp);
			
			// delay for one second ish, note difrent clock so delay is not acurate
			for(uint8_t j = 0; j<80;j++){
				_delay_ms(100);
			}
		}
    }
}


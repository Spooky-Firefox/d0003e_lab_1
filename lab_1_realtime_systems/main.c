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
struct digit_reg* scc_to_digit_reg(struct digit_reg* digit, uint16_t scc){
	digit->x0 = (uint8_t)(scc & 0x000f);
	digit->x5 = (uint8_t)((scc & 0x00f0) >> 4);
	digit->x10 = (uint8_t)((scc & 0x0f00) >> 8);
	digit->x15 = (uint8_t)((scc & 0xf000) >> 12);
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

// the function defined in part one of the lab
// 0 no error
// 1 pos out of range
uint8_t writeChar(char ch, uint8_t pos){
	// to test if pos is out of range
	uint8_t err = 0x00;
	if (pos > 5){
		err = err | 0x01;
	}
	if(err){
		return err;
	}
	
	// convert char num to uint8
	uint8_t num = ch-0x30;
	struct digit_reg digit = {0,0,0,0};
	// if the char is is a valid number convert the digit to represent it
	if (num < 10){
		scc_to_digit_reg(&digit,numbers[num]);
	}
	
	// calculate the register and if its the low or high nibble to write to
	volatile uint8_t* reg = &LCDDR0 + pos/2;
	uint8_t is_right = pos % 2;
	
	if(is_right){
		and_digit_reg(reg,0x0f);
		digit_reg_to_right(&digit);
	} else {
		and_digit_reg(reg,0xf0);
	}
	
	write_over_digit_reg(reg,&digit);
	return err;
}

//write long, NOTE ONLY USES FIRST 3 digit scince display is broken
void writeLong(long i){
	char first = i%10;
	i = i/10;
	char second = i%10;
	i = i/10;
	char third = i%10;
	writeChar(first+0x30,2);
	writeChar(second+0x30,1);
	writeChar(third+0x30,0);
}


int main(void)
{	
	setupLCD();


    writeLong(123);
}


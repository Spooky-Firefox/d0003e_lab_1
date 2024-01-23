#pragma once

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
void scc_to_digit_reg();

// converts a digit_reg struct to have char at right by shifting the bits
void digit_reg_to_right();

void setupLCD();

// writes a char over current segments by using or on the registers
void write_over_digit_reg(volatile uint8_t* reg_ptr, struct digit_reg *digit);

// and the relevant digit register with the mask, useful for clearing digits
void and_digit_reg(volatile uint8_t* reg_ptr, uint8_t mask);

void toogle_s1();

// the function defined in part one of the lab
// 0 no error
// 1 pos out of range
uint8_t writeChar(char ch, uint8_t pos);

void writeLong(long i);
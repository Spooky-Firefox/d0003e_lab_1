#pragma once

// Enables the lcd and sets up its parameters
void setupLCD();

// toggles the 1 above the first char
void toggle_s1();

// the function defined in part one of the lab
// 0 no error
// 1 pos out of range
uint8_t writeChar(char ch, uint8_t pos);

void writeLong(long i);
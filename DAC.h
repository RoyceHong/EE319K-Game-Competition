// DAC.h

#ifndef DAC_H
#define DAC_H

#include <stdint.h>

// **************DACInit*********************
// Initialize 8-bit DAC, called once 
// Input: none
// Output: none
void DACInit(void);

// **************DACOut*********************
// output to DAC
// Input: 8-bit data, 0 to 255 
// Input=n is converted to n*3.3V/15
// Output: none
void DACOut(uint8_t data);

#endif

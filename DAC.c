// DAC.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Hardware connections: PortB.0-7 (Bit 0 is least significant bit)

#include <stdint.h>
#include "tm4c123gh6pm.h"


#include "DAC.h"

// **************DACInit*********************
// Initialize 8-bit DAC, called once 
// Input: none
// Output: none
void DACInit(void)
{
    // Turn on port A
    SYSCTL_RCGC2_R |= 0x02;
    __asm{NOP};
    __asm{NOP};
    // All pins are digital outputs
    GPIO_PORTB_AMSEL_R = 0x00; 
    GPIO_PORTB_PCTL_R = 0x00;
    GPIO_PORTB_DIR_R = 0xFF;
    GPIO_PORTB_AFSEL_R = 0x00;
    GPIO_PORTB_DEN_R = 0xFF;
}


// **************DACOut*********************
// output to DAC
// Input: 8-bit data, 0 to 255 
// Input=n is converted to n*3.3V/15
// Output: none
void DACOut(uint8_t data)
{
    GPIO_PORTB_DATA_R = data;
}

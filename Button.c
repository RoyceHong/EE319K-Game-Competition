// Button.c

#include <stdint.h>
#include "Button.h"
#include "tm4c123gh6pm.h"

void Button_Init(){
    // Enable clock
    SYSCTL_RCGCGPIO_R |= 0x10;
    __asm{NOP};
    __asm{NOP};
    // E0-2 digital inputs
    GPIO_PORTE_AMSEL_R &= ~0x01;
    GPIO_PORTE_PCTL_R &= ~0x01;
    GPIO_PORTE_DIR_R &= ~0x01;
    GPIO_PORTE_AFSEL_R &= ~0x01;
    GPIO_PORTE_DEN_R |= 0x01;
}

uint8_t Button_In(void){
    return(GPIO_PORTE_DATA_R & 0x01);
}



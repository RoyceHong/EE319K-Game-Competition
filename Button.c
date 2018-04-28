// Button.c

#include <stdint.h>
#include "Button.h"
#include "tm4c123gh6pm.h"

uint8_t buttonStatus = 0;

void Button_Init(){
    // Enable clock
    SYSCTL_RCGCGPIO_R |= 0x10;
    __asm{NOP};
    __asm{NOP};
    // PE0 digital inputs
    GPIO_PORTE_AMSEL_R &= ~0x02;
    GPIO_PORTE_PCTL_R &= ~0x02;
    GPIO_PORTE_DIR_R &= ~0x02;
    GPIO_PORTE_AFSEL_R &= ~0x02;
    GPIO_PORTE_DEN_R |= 0x02;
    
    
    // set up edge-triggered interrupt for button
    // edge triggered interrupt on PE0
    GPIO_PORTE_IS_R &= ~0x02;
    // set to single-edge interrupt
    GPIO_PORTE_IBE_R &= ~0x02;
    // Set PE0 to trigger on falling edge
    GPIO_PORTE_IEV_R &= ~0x02;
    // arm interrupt on PE0
    GPIO_PORTE_IM_R |= 0x02;
    // Priority set to 1
    NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFFFF00)|0x00000020;
    // enable interrupt 20 in NVIC
    NVIC_EN0_R = 0x00000010;
}


uint8_t Button_In(void){
    return(GPIO_PORTE_DATA_R & 0x02);
}


void GPIOPortE_Handler(void){
    GPIO_PORTE_ICR_R = 0x02; 
    // acknowledge flag 0 
    buttonStatus = 1;
}


void DisableEdgeInt(void){
    GPIO_PORTE_IM_R &= ~0x02;
}



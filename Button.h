// Button.h


#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>


// Initialize Port E buttons and edge-triggered interrupt
void Button_Init(void);


uint8_t Button_In(void);


// Edge-triggered interrupt ISR
void GPIOPortE_Handler(void);


// Disables the edge interrupt on button 
void DisableEdgeInt(void);

#endif


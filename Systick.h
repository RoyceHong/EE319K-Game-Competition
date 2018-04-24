// Systick.h 
// Initializes SysTick and holds SysTick Interrupt Service Routine

#ifndef SYSTICK_H
#define SYSTICK_H


// SysTick Initialization Function
// Initializes SysTick to interrupt at exactly 30Hz
void SysTick_Init(void);


// SysTick Interrupt Service Routine
void SysTick_Handler(void);


#endif

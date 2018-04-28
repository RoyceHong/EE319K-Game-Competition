// DisplayMap.h 

#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H

#include <stdint.h>
#include "player.h"

#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH 128
#endif

#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT 160
#endif


// ***************** Timer0_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
// **********************************************
void Timer0_Init(void);


// Timer0 Interrupt Service Routine
void Timer0A_Handler(void);

#endif



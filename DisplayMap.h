// DisplayMap.h 

#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H

#include <stdint.h>
#include "level.h"

#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH 128
#endif

#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT 50
#endif


// ***************** Timer0_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
// **********************************************
void Timer0_Init(void);


// Clear both buffers to all black 
// Called once at the beginning of the game 
void Buffer_Init(void);


// Draw image to background buffer 
void DrawImage_Buffer(sprite_t *object, uint16_t Buff[DISPLAY_HEIGHT][DISPLAY_WIDTH]);


// fills current image with black rectangle
//void Image_Clear(int16_t x,  int16_t y, int16_t w, int16_t h, uint16_t Buff[DISPLAY_HEIGHT][DISPLAY_WIDTH]);


// Timer0 Interrupt Service Routine
void Timer0A_Handler(void);

#endif



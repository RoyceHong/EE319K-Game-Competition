// DisplayMap.c

#include "DisplayMap.h"
#include "tm4c123gh6pm.h"
#include "ST7735.h"

// Display buffers
uint16_t Buffer1[160][128];

uint16_t Buffer2[160][128];

// ***************** Timer0_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer0_Init(void){
    SYSCTL_RCGCTIMER_R |= 0x01;
    // Disable timer
    TIMER0_CTL_R = 0x00000000;
    // 32-bit mode
    TIMER0_CFG_R = 0x00000000;
    // Periodic mode
    TIMER0_TAMR_R = 0x000000002;
    // Set reload value
    TIMER0_TAILR_R = 2666667;
    // Use bus clock
    TIMER0_TAPR_R = 0;
    // Clear timeout flag
    TIMER0_ICR_R = 0x000000001;
    // Enable interrupt
    TIMER0_IMR_R = 0x000000001;
    // Set priority to the same as the main timer
    NVIC_PRI4_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000;
    // Enable IRQ 19 in NVIC
    NVIC_EN0_R = 1<<19;
    // Enable timer
    TIMER0_CTL_R = 0x00000001;
}


// Clear both buffers to all black 
// Called once at the beginning of the game 
void Buffer_Init(){
    uint8_t i, j;
    for(i = 0; i < DISPLAY_HEIGHT; i++){
        for(j = 0; j < DISPLAY_WIDTH; j++){
            Buffer1[i][j] = 0x0000;
            Buffer2[i][j] = 0x0000;
        }
    }
}


// Draw image to background buffer 
void DrawImage_Buffer(int16_t x,  int16_t y, const uint16_t *image, int16_t w, int16_t h, uint16_t Buff[160][128]){
    uint32_t counter = 0;
	for(int a = 0; a < h; a++){			// Index Y axis
		for(int b = 0; b < w; b++){		// Index X axis
			Buff[y+a][x+b] = image[counter];
			counter ++;
		}
	}
}


void Image_Clear(int16_t x,  int16_t y, int16_t w, int16_t h, uint16_t Buff[160][128]){
    uint32_t counter = 0;
	for(int a = 0; a < h; a++){			// Index Y axis
		for(int b = 0; b < w; b++){		// Index X axis
			Buff[y+a][x+b] = 0x0000;
			counter ++;
		}
	}
}


// Timer0 Interrupt Service Routine 
void Timer0A_Handler(void){
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER0A timeout
    ST7735_DrawBitmap(0, 160, *Buffer1, 128, 160);
}



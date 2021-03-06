// Systick.c 
// Initializes SysTick and holds SysTick Interrupt Service Routine

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "adc.h"
#include "movement.h"
#include "Player.h" 

extern sprite_t PlayerHell;
extern sprite_t Player1;
uint8_t playerflag = 0;
extern uint8_t spaceInvadersRestriction;
movestate_t CurrentMove;
// flag_t MoveStatus = BUSY;

// Initializes SysTick
void SysTick_Init(void){
    // Disable interrupts during setup
    NVIC_ST_CTRL_R = 0;
    // Set priority to 2
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000;
    // Set up interrupts with clock (bit 2) mode 1
    NVIC_ST_CTRL_R = 0x0000007;
    // Initialize SysTick to interrupt at 30Hz
    NVIC_ST_RELOAD_R = 1333333;
    NVIC_ST_CURRENT_R = 0;
}


void SysTick_Handler(void){
    CurrentMove = ADC_Convert();
    if(spaceInvadersRestriction == 1){
        Process_Move(&Player1, CurrentMove);
    }
    else{
        Process_Move(&PlayerHell, CurrentMove);
    }
    playerflag = 1; 
}
    

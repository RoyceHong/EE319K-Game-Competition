// ADC.h
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0

#ifndef ADC_H
#define ADC_H
#include <stdint.h>


// Player position structure
typedef struct Player_Pos{
    int16_t x;
    int16_t y;
} Player_Pos;


// Move state enum 
typedef enum move_state {LEFT, HOLD, RIGHT} MoveState;


typedef uint8_t FSM; 
    

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void);


//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void);


//------------ADC_Convert------------
// Converts ADC_In to a position on the LCD
// Input: none
// Output: none
MoveState ADC_Convert(void);

#endif

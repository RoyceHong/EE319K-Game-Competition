// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ADC.h"

//------------ADC_Init------------
// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
//--------------------------------
void ADC_Init(void){ 
    
    // activate clock ADC0
    SYSCTL_RCGCADC_R |= 0x01;       
    __asm{NOP};
    __asm{NOP};
    
    // set up PD2 as analog input to ADC 
    SYSCTL_RCGCGPIO_R |= 0x08;
    __asm{NOP};
    __asm{NOP};
    GPIO_PORTD_DIR_R &= ~0x04;
    GPIO_PORTD_AFSEL_R |= 0x04;
    GPIO_PORTD_DEN_R &= ~0x04;
    GPIO_PORTD_AMSEL_R |= 0x04;
    
    ADC0_PC_R = 0x01;               // configure 125kHz ADC conversion speed
    ADC0_SSPRI_R = 0x0123;          // set priorities
    ADC0_ACTSS_R &= ~0x08;        // disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;         // seq3 is set to software trigger
    ADC0_SSMUX3_R &= ~0x0F;
    ADC0_SSMUX3_R |= 0x05;          // set channel to Ain5 (PD2)
    ADC0_SSCTL3_R = 0x06;
    ADC0_SAC_R = 0x03;
    ADC0_IM_R &= ~0x08;             // disable ss3 interrupts
    ADC0_ACTSS_R |= 0x08;           // enable ss3
    

/*
// DEBUG FOR JOYSTICK
// activate clock ADC0
    SYSCTL_RCGCADC_R |= 0x01;       
    __asm{NOP};
    __asm{NOP};
    
    // set up PD2 as analog input to ADC 
    SYSCTL_RCGCGPIO_R |= 0x08;
    __asm{NOP};
    __asm{NOP};
    GPIO_PORTD_DIR_R &= ~0x06;
    GPIO_PORTD_AFSEL_R |= 0x06;
    GPIO_PORTD_DEN_R &= ~0x06;
    GPIO_PORTD_AMSEL_R |= 0x06;
    
    ADC0_PC_R = 0x01;               // configure 125kHz ADC conversion speed
    ADC0_SSPRI_R = 0x0123;          // set priorities
    ADC0_ACTSS_R &= ~0x04;        // disable sample sequencer 2
    ADC0_EMUX_R &= ~0x0F00;         // seq3 is set to software trigger
    ADC0_SSMUX2_R &= ~0x00FF;
    ADC0_SSMUX2_R |= 0x0056;          // set channel to Ain5 (PD2)
    ADC0_SSCTL2_R = 0x0064;
    ADC0_SAC_R = 0x00;
    ADC0_IM_R &= ~0x04;             // disable ss3 interrupts
    ADC0_ACTSS_R |= 0x04;           // enable ss3
// END OF DEBUG FOR JOYSTICK
*/
}


//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
//------------------------------
uint32_t ADC_In(void){
    uint32_t data; 
    // initiate ss3
    ADC0_PSSI_R = 0x08;
    // wait for conversion to be completed 
    while((ADC0_RIS_R & 0x08) == 0){};
    // read result
    data = ADC0_SSFIFO3_R &0xFFF;
    // clear sample complete flag 
    ADC0_ISC_R = 0x08;
    return data; 
    
/*    
    //  DEBUG FOR JOYSTICK
    uint32_t data; 
    // initiate ss3
    ADC0_PSSI_R = 0x04;
    // wait for conversion to be completed 
    while((ADC0_RIS_R & 0x04) == 0){};
    // read result
    data = ADC0_SSFIFO2_R &0xFFF;
    // clear sample complete flag 
    ADC0_ISC_R = 0x04;
    return data; 
    // END OF DEBUG FOR JOYSTICK
*/
}


//------------ADC_Convert------------
// Converts analog signal to a direction: LEFT, HOLD, RIGHT
// Input: none
// Output: enum MoveState {LEFT, HOLD, RIGHT}
//-----------------------------------
movestate_t ADC_Convert(void){
    uint32_t data;
    data = ADC_In();
    if(data <= 1365){
        return LEFT;
    }
    else if(data >= 2730){
        return RIGHT;
    }
    else{
        return HOLD;
    }
    
    // UP/DOWN code for y axis
}

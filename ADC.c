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
    SYSCTL_RCGCADC_R |= 0x03;       
    __asm{NOP};
    __asm{NOP};
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
    
    // X axis potentiometer
    ADC0_PC_R = 0x01;               // configure 125kHz ADC conversion speed
    ADC0_SSPRI_R = 0x0123;          // set priorities
    ADC0_ACTSS_R &= ~0x08;        // disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;         // seq3 is set to software trigger
    ADC0_SSMUX3_R &= ~0x0F;
    ADC0_SSMUX3_R |= 0x05;          // set channel to Ain5 (PD2)
    ADC0_SSCTL3_R = 0x06;
    ADC0_SAC_R = 0x00;
    ADC0_IM_R &= ~0x08;             // disable ss3 interrupts
    ADC0_ACTSS_R |= 0x08;           // enable ss3
    
    // Y axis potentiometer
    ADC1_PC_R = 0x01;               // configure 125kHz ADC conversion speed
    ADC1_SSPRI_R = 0x0123;          // set priorities
    ADC1_ACTSS_R &= ~0x04;        // disable sample sequencer 3
    ADC1_EMUX_R &= ~0x0F00;         // seq3 is set to software trigger
    ADC1_SSMUX2_R &= ~0x0F;
    ADC1_SSMUX2_R |= 0x06;          // set channel to Ain6 (PD2)
    ADC1_SSCTL2_R = 0x06;
    ADC1_SAC_R = 0x00;
    ADC1_IM_R &= ~0x04;             // disable ss3 interrupts
    ADC1_ACTSS_R |= 0x04;           // enable ss3
}


//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
//------------------------------
uint32_t ADC_InX(void){
    uint32_t xdata; 
    // initiate ss3
    ADC0_PSSI_R = 0x08;
    // wait for conversion to be completed 
    while((ADC0_RIS_R & 0x08) == 0){};
    // read result
    xdata = ADC0_SSFIFO3_R &0xFFF;
    // clear sample complete flag 
    ADC0_ISC_R = 0x08;
    return xdata; 
}


uint32_t ADC_InY(void){
    uint32_t ydata; 
    // initiate ss3
    ADC1_PSSI_R = 0x04;
    // wait for conversion to be completed 
    while((ADC1_RIS_R & 0x04) == 0){};
    // read result
    ydata = ADC1_SSFIFO2_R &0xFFF;
    // clear sample complete flag 
    ADC1_ISC_R = 0x04;
    return ydata; 
}


//------------ADC_Convert------------
// Converts analog signal to a direction: LEFT, HOLD, RIGHT
// Input: none
// Output: enum MoveState
//-----------------------------------
movestate_t ADC_Convert(void){
    uint32_t xdata, ydata;
    xdata = ADC_InX();
    ydata = ADC_InY();
    if(xdata <= 1365 && ydata > 1365 && ydata < 2730){
        return LEFT;
    }
    else if(xdata >= 2730 && ydata > 1365 && ydata < 2730){
        return RIGHT;
    }
    else if(ydata <= 1365 && xdata > 1365 && xdata < 2730){
        return UP;
    }
    else if(ydata >= 2730 && xdata > 1365 && xdata < 2730){
        return DOWN;
    }
    else if(xdata <= 1365 && ydata >=2730){
        return DOWNLEFT;
    }
    else if(xdata >= 2730 && ydata >=2730){
        return DOWNRIGHT;
    }
    else if(xdata <= 1365 && ydata <= 1365){
        return UPLEFT;
    }
    else if(xdata >= 2730 && ydata <= 1365){
        return UPRIGHT;
    }
    else{
        return HOLD;
    }
}

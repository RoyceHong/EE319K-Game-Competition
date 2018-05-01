// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 11/21/2017 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2017

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2017

 Copyright 2017 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PE2/AIN1
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "Systick.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "MainMenu.h"
#include "Button.h"
#include "DisplayMap.h"
#include "MainMenu.h" 
#include "Boss.h"
#include "BulletHell.h"
#include "CutScene.h"
#include "Sound.h"
#include "BattleSelect.h" 


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds

extern uint32_t Score;
extern const uint16_t FinalScore[];
extern scene_t Sayaka_Stage1[];
extern scene_t Sayaka_Stage2[];
extern scene_t Sayaka_Stage3[];
extern uint8_t bossNum;
uint8_t GameOn = 1;

extern progress_t gameProgress;


int main(void){
    // Initializations
    PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
    ST7735_InitR(INITR_REDTAB);
    Sound_Init();
    
    // Initializations for main menu
    ADC_Init();
    SysTick_Init();
    Button_Init();
    // Enable Interrupts
    EnableInterrupts();
    //  Print main menu on the screen 
    Menu();

    SpaceInvadersInit();
    gameProgress = IN_PROGRESS;
    while(gameProgress == IN_PROGRESS){
        SpaceInvaders();
    }

    
    SceneMain(Sayaka_Stage1);   
   
    BattleStartInit();
    gameProgress = IN_PROGRESS;
    while(gameProgress == IN_PROGRESS){
        if(GameOn == 1){
            BattleStart();
        }
        if(GameOn == 0){
            GameOver();
        }
    }
    bossNum++;
    SceneMain(Sayaka_Stage2);   
    
    BattleStartInit();
    gameProgress = IN_PROGRESS;
    while(gameProgress == IN_PROGRESS){
        if(GameOn == 1){
            BattleStart();
        }
        if(GameOn == 0){
            GameOver();
        }
    }
    
    bossNum++;
    SceneMain(Sayaka_Stage3);
    
    BattleStartInit();
    gameProgress = IN_PROGRESS;
    while(gameProgress == IN_PROGRESS){
        if(GameOn == 1){
            BattleStart();
        }
        if(GameOn == 0){
            GameOver();
        }
    }
    
    ST7735_FillRect(0, 0 , DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    ST7735_DrawBitmap(0, 51, FinalScore, 128, 51); 
    ST7735_SetCursor(9, 4);
    LCD_OutDec(Score);
    while(Button_In() == 0){}
    while(Button_In() != 0){}

}


// You can use this timer only if you learn how it works
void Delay100ms(uint32_t count){uint32_t volatile time;
    while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
        time--;
    }
    count--;
    }
}


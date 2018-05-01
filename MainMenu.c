// MainMenu.c

#include <stdint.h>
#include "ST7735.h"
#include "Player.h"
#include "MainMenu.h"
#include "DisplayMap.h"
#include "ADC.h"
#include "Sound.h"
#include "Button.h"
#include "Random.h"
#include "tm4c123gh6pm.h"
#include "BattleSelect.h"

void Delay100ms(uint32_t count);

extern uint8_t spaceInvadersRestriction;
extern uint8_t GameOn;
extern const uint16_t Retry[];
extern const uint16_t GameOverImg[];
extern const uint16_t CuteAlien[];
extern const uint16_t MainMenu[];
extern const uint16_t SadFace[];
extern movestate_t CurrentMove;
extern uint8_t buttonStatus;
uint8_t PlayerHasDied = 0;
extern progress_t gameProgress;

// Coordinates for play: (33, 95)
// Coordinates for quit: (33, 111) 

// Cursor intiailly set to PLAY
cursor_t MenuCursor = {CURSORX, PLAYY, CuteAlien, 13, 10};

// Prints the Main Menu on the screen 
void Menu(){
    ST7735_DrawBitmap(0, DISPLAY_HEIGHT, MainMenu, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ST7735_DrawBitmap(MenuCursor.x, MenuCursor.y, MenuCursor.image, MenuCursor.w, MenuCursor.h);
    // Loop until button press selects what to do 
    while(buttonStatus != 1){
            UpdateMenu();
        }
        MenuChoice();
        Delay100ms(10);
        Random_Init(NVIC_ST_CURRENT_R);
}


void UpdateMenu(void){
    if(CurrentMove == UP && MenuCursor.y != PLAYY){
        // Erase cursor
        ST7735_FillRect(MenuCursor.x, MenuCursor.y - MenuCursor.h, MenuCursor.w, MenuCursor.h, 0);
        MenuCursor.y = PLAYY; 
        SelectSound(MENU_SOUND_1);
        // Redraw cursor at new position
        ST7735_DrawBitmap(MenuCursor.x, MenuCursor.y, MenuCursor.image, MenuCursor.w, MenuCursor.h);
    }
    else if(CurrentMove == DOWN && MenuCursor.y != QUITY){
        // Erase cursor
        ST7735_FillRect(MenuCursor.x, MenuCursor.y - MenuCursor.h, MenuCursor.w, MenuCursor.h, 0);
        MenuCursor.y = QUITY;
        SelectSound(MENU_SOUND_1);
        // Redraw cursor at new position 
        ST7735_DrawBitmap(MenuCursor.x, MenuCursor.y, MenuCursor.image, MenuCursor.w, MenuCursor.h);
    }
}


void MenuChoice(void){
    SelectSound(MENU_SOUND_2);
    if(MenuCursor.y == QUITY){
        ST7735_FillRect(0, 0 , DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
        ST7735_DrawBitmap(44, 105, SadFace, 40, 50);
        while(1){}
    }
}


void GameOver(void){
    uint8_t retrybutton = Button_In();
    PlayerHasDied = 1;
    SelectSound(GAME_OVER_SOUND);
    ST7735_FillRect(0, 0 , DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    ST7735_DrawBitmap(14, 40, GameOverImg, 100, 25);
    ST7735_DrawBitmap(37, 80, Retry, 55, 16);
    ST7735_DrawBitmap(15, 76, CuteAlien, 13, 10);
    Delay100ms(3);
    while(retrybutton == 0x02){
        retrybutton = Button_In();
    }
    while(retrybutton != 0x02){
        retrybutton = Button_In();
    }
    ST7735_FillRect(0, 0 , DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    if(spaceInvadersRestriction == 1){
        SpaceInvadersInit();
    }
    else{
        BattleStartInit();
    }  
    GameOn = 1;
    gameProgress = IN_PROGRESS;
}


// MainMenu.c

#include <stdint.h>
#include "ST7735.h"
#include "Player.h"
#include "MainMenu.h"
#include "DisplayMap.h"
#include "ADC.h"
#include "Sound.h"

extern const uint16_t CuteAlien[];
extern const uint16_t MainMenu[];
extern const uint16_t SadFace[];
extern movestate_t CurrentMove;

// Coordinates for play: (33, 95)
// Coordinates for quit: (33, 111) 

// Cursor intiailly set to PLAY
cursor_t MenuCursor = {CURSORX, PLAYY, CuteAlien, 13, 10};

// Prints the Main Menu on the screen 
void Menu(){
    ST7735_DrawBitmap(0, DISPLAY_HEIGHT, MainMenu, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ST7735_DrawBitmap(MenuCursor.x, MenuCursor.y, MenuCursor.image, MenuCursor.w, MenuCursor.h);
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


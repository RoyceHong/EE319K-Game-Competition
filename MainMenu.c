// MainMenu.c

#include <stdint.h>
#include "ST7735.h"
#include "Player.h"
#include "MainMenu.h"
#include "DisplayMap.h"
#include "ADC.h"

extern const uint16_t CuteAlien[];
extern const uint16_t MainMenu[];
movestate_t CursorState;

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
    if(CursorState == UP){
        MenuCursor.y = PLAYY;
    }
    else if(CursorState == DOWN){
        MenuCursor.y = QUITY;
    }
    // Erase cursor
    ST7735_FillRect(MenuCursor.x, MenuCursor.y - MenuCursor.h, MenuCursor.w, MenuCursor.h, 0);
    // Redraw cursor at new position 
    ST7735_DrawBitmap(MenuCursor.x, MenuCursor.y, MenuCursor.image, MenuCursor.w, MenuCursor.h);
}


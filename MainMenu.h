// MainMenu.h

#ifndef MAINMENU_H
#define MAINMENU_H

#include <stdint.h>

#ifndef CURSORX
#define CURSORX 33
#endif

#ifndef PLAYY
#define PLAYY 95
#endif

#ifndef QUITY
#define QUITY 111
#endif


typedef enum {SUCCESS, IN_PROGRESS, FAIL} progress_t;


typedef struct cursor_t{
    int16_t x;
    int16_t y;
    const uint16_t* image;
    int16_t w;
    int16_t h;
}cursor_t;
    
    
// Prints the main menu on the screen 
void Menu(void);


// Moves the cursor 
void UpdateMenu(void);


// Processes the menu choice
void MenuChoice(void);


void GameOver(void);

#endif

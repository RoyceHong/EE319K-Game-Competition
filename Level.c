// Level.c 

#include <stdint.h>
#include "level.h"
#include "sprites.h"
#include "ST7735.h"
#include "DisplayMap.h"

extern uint16_t Buffer1[DISPLAY_HEIGHT][DISPLAY_WIDTH];

// Player1 initial definition 
sprite_t Player1 = {52,  159,  PlayerRightFrame_1,  16, 11, 0, 0, ALIVE};

// array definition of enemies 
sprite_t Enemies[ENEMY_ROW][ENEMY_COLUMN];


// Bunker initial definition
sprite_t Bunker1 = {25, 140, Bunker0, 18, 5, 0, 0, ALIVE};
sprite_t Bunker2 = {90, 140, Bunker0, 18, 5, 0, 0, ALIVE}; 


// Initializes the first space invaders level
void Level_Init(){
    uint8_t i, j;
    // Fill enemy array 
    for( i = 0; i < ENEMY_ROW; i++ ){
        for( j = 0; j < ENEMY_COLUMN; j++ ){
            Enemies[i][j].x = j*20; 
            Enemies[i][j].y = (20+20*i);
            Enemies[i][j].w = 13;
            Enemies[i][j].h = 10;
            Enemies[i][j].xvel = 1;
            Enemies[i][j].yvel = 1;
            Enemies[i][j].image = CuteAlien; 
            Enemies[i][j].life = ALIVE;
        }
    }
    
    // Make screen blank 
    ST7735_FillScreen(0x0000);
    
    // Draw bunker on screen
    ST7735_DrawBitmap(Bunker1.x, Bunker1.y,  Bunker1.image, Bunker1.w, Bunker1.h);
    ST7735_DrawBitmap(Bunker2.x, Bunker2.y,  Bunker2.image, Bunker2.w, Bunker2.h);
    
    // Draw player on screen
    ST7735_DrawBitmap(Player1.x, Player1.y, Player1.image, Player1.w,  Player1.h);
       
    // Draw enemies on screen
    for( i = 0; i < ENEMY_ROW; i++ ){
        for( j = 0; j < ENEMY_COLUMN; j++ ){
            ST7735_DrawBitmap(Enemies[i][j].x, Enemies[i][j].y, Enemies[i][j].image, Enemies[i][j].w,  Enemies[i][j].h);
        }
    }
}





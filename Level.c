// Level.c 

#include <stdint.h>
#include "level.h"
#include "sprites.h"
#include "ST7735.h"
#include "DisplayMap.h"

extern uint16_t Buffer1[160][128];

extern uint16_t Buffer2[160][128];

// Player1 initial definition 
player_t Player1 = {52,  159,  PlayerRightFrame_1,  11, 16, ALIVE};

/*
// Enemy initial definitions
Enemy Enemy1     = {0,      10,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy2     = {20,     10,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy3     = {40,     10,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy4     = {60,     10,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy5     = {80,     10,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy6     = {100,    10,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy7     = {0,      30,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy8     = {20,     30,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy9     = {40,     30,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy10    = {60,     30,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy11    = {80,     30,     CuteAlien,   13,     10,     ALIVE};
Enemy Enemy12    = {100,    30,     CuteAlien,   13,     10,     ALIVE};
*/

// array definition of enemies 
enemy_t Enemies[2][6];


// Initializes all players and enemies 
// Called at the beginning of the game 
void Level_Init(){
    uint8_t i, j;
    // Make screen blank 
    ST7735_FillScreen(0x0000);
    // Draw player on initial buffer
    DrawImage_Buffer(Player1.x, Player1.y, Player1.image, Player1.w, Player1.h, Buffer1);
    
    // Fill enemy array 
    for( i = 0; i < 2; i++ ){
        for( j = 0; j < 6; j++ ){
            Enemies[i][j].x = j*20; 
            Enemies[i][j].y = (10+20*i);
            Enemies[i][j].w = 13;
            Enemies[i][j].h = 10;
            Enemies[i][j].image = CuteAlien; 
            Enemies[i][j].life = ALIVE;
        }
    }
    
    // Fill initial buffer with enemies
    for( i = 0; i < 2; i++ ){
        for( j = 0; j < 6; j++ ){
            DrawImage_Buffer(Enemies[i][j].x, Enemies[i][j].y, Enemies[i][j].image, Enemies[i][j].w, Enemies[i][j].h, Buffer1);
        }
    }
    
}




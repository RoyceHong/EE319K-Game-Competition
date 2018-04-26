// Enemy.c

#include <stdint.h>
#include "sprites.h"
#include "Movement.h"
#include "ST7735.h"
#include "enemy.h"
#include "DisplayMap.h"

// array definition of enemies 
sprite_t Enemies[ENEMY_ROW][ENEMY_COLUMN];
// flag that notifies when the enemy should move down, set when enemies hit border of screen
uint8_t enemydown = 0;
// timer for when the aliens move horizontally
uint32_t enemyxtime = ENEMY_XTIMER;


void Enemy_Init(){
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
    
    // Draw enemies on screen
    for( i = 0; i < ENEMY_ROW; i++ ){
        for( j = 0; j < ENEMY_COLUMN; j++ ){
            ST7735_DrawBitmap(Enemies[i][j].x, Enemies[i][j].y, Enemies[i][j].image, Enemies[i][j].w,  Enemies[i][j].h);
        }
    }
}

// Moves the enemy in either the x or y direction 
void Move_Enemy(){
    uint8_t i, j;
    
    // moves enemies in the horizontal direction
    if(enemyxtime == 0){
        // reset enemy timer 
        enemyxtime = ENEMY_XTIMER;
        // Check enemy positions and set velocity values  
        for( i = 0; i < ENEMY_ROW; i++ ){
            for( j = 0; j < ENEMY_COLUMN; j++ ){
                if(Enemies[i][j].life == DEAD){}  
                else if(Enemies[i][j].x <= 0){
                    Fill_Enemy(1);
                    enemydown = 1;
                    goto CheckDone;
                }
                else if(Enemies[i][j].x + Enemies[i][j].w >= DISPLAY_WIDTH){
                    Fill_Enemy(-1);
                    enemydown = 1;
                    goto CheckDone;
                }
            }
        }
        CheckDone:
        // Move enemies 
        for( i = 0; i < ENEMY_ROW; i++ ){
            for( j = 0; j < ENEMY_COLUMN; j++ ){
                MoveX(&Enemies[i][j]);
            }
        }
    }
    else{
        enemyxtime--;
    }
    
    // moves enemy in the vertical direction if the enemydown flag is set
    if(enemydown == 1){
        enemydown = 0;
        for( i = 0; i < ENEMY_ROW; i++ ){
            for( j = 0; j < ENEMY_COLUMN; j++ ){
                MoveY(&Enemies[i][j]);
            }
        }   
    }
}


// Rewrites all the xvel values for the enemies 
void Fill_Enemy(int8_t velocity){
    uint8_t i, j;
    // Fill enemy array with xvel and yvel values
    for( i = 0; i < ENEMY_ROW; i++ ){
        for( j = 0; j < ENEMY_COLUMN; j++ ){
            Enemies[i][j].xvel = velocity;
        }
    }
}






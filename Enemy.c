// Enemy.c

#include <stdint.h>
#include "Movement.h"
#include "ST7735.h"
#include "enemy.h"
#include "DisplayMap.h"
#include "MainMenu.h"

extern const uint16_t Bunker0[];
extern const uint16_t CuteAlien[];
extern progress_t gameProgress;

// array definition of enemies 
sprite_t Enemies[ENEMY_ROW][ENEMY_COLUMN];
// flag that notifies when the enemy should move down, set when enemies hit border of screen
uint8_t enemydown = 0;
// timer for when the aliens move horizontally
uint32_t enemyxtime = ENEMY_XTIMER;

// Bunker initial definition
sprite_t Bunkers[OBSTACLE_SIZE] = { 
    {25, 140, Bunker0, 18, 5, 0, 0, ALIVE}, 
    {90, 140, Bunker0, 18, 5, 0, 0, ALIVE}
};


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


void Enemy_Dead(void){
    uint8_t i, j;
    uint32_t numAlive = 0;
    for( i = 0; i < ENEMY_ROW; i++ ){
        for( j = 0; j < ENEMY_COLUMN; j++ ){
            if(Enemies[i][j].life == ALIVE){
                numAlive ++;
            }
        }
    }
    
    // game over by defeating all enemes
    // status is success
    if(numAlive == 0){
        gameProgress = SUCCESS;
    }
}


void Bunker_Init(void){   
    // Draw bunker on screen
    ST7735_DrawBitmap(Bunkers[0].x, Bunkers[0].y,  Bunkers[0].image, Bunkers[0].w, Bunkers[0].h);
    ST7735_DrawBitmap(Bunkers[1].x, Bunkers[1].y,  Bunkers[1].image, Bunkers[1].w, Bunkers[1].h);
}






// Movement.c


#include <stdint.h>
#include "movement.h"
#include "adc.h"
#include "level.h"
#include "DisplayMap.h"
#include "ST7735.h"

//extern uint16_t Buffer1[DISPLAY_HEIGHT][DISPLAY_WIDTH];
extern sprite_t Enemies[ENEMY_ROW][ENEMY_COLUMN];

// Process_Move
// Converts direction enum into velocity value
void Process_Move(sprite_t* player, movestate_t xdirection){
    switch(xdirection){
        case LEFT:
            player -> xvel = -1;
            break;
        case HOLD:
            player -> xvel = 0;
            break;
        case RIGHT: 
            player -> xvel = 1;
            break;
    }
}


// Universal move function, takes sprite as input and moves according to xvel and yvel
void Move(sprite_t* object){
    if( ((object -> x + object -> xvel) >= 0) && ((object -> x + object -> xvel + object -> w) <= DISPLAY_WIDTH) ){
        (object -> x) = (object -> x) + (object -> xvel);
    }
    if( ((object -> y + object -> yvel) >= 0) && ((object -> y + object -> yvel + object -> h) <= DISPLAY_HEIGHT) ){
        object -> y = object -> y + object -> yvel;
    }
    ST7735_DrawBitmap(object -> x, object -> y, object -> image, object -> w, object -> h);
}


void Move_Enemy(enemdir_t direction){
    uint8_t i, j;
    // Check enemy positions and set velocity values  
    if(direction == X){
        for( i = 0; i < ENEMY_ROW; i++ ){
            for( j = 0; j < ENEMY_COLUMN; j++ ){
                if(Enemies[i][j].life == DEAD){}  
                else if(Enemies[i][j].x <= 0){
                    Fill_Enemy(1);
                    goto CheckDone;
                }
                else if(Enemies[i][j].x + Enemies[i][j].w >= DISPLAY_WIDTH){
                    Fill_Enemy(-1);
                    goto CheckDone;
                }
            }
        }
        CheckDone:
        // Move enemies 
        for( i = 0; i < ENEMY_ROW; i++ ){
            for( j = 0; j < ENEMY_COLUMN; j++ ){
                Move(&Enemies[i][j]);
            }
        }
    }
    else if(direction == Y){
        for( i = 0; i < ENEMY_ROW; i++ ){
            for( j = 0; j < ENEMY_COLUMN; j++ ){
                Move(&Enemies[i][j]);
            }
        }
    }        
}


void Fill_Enemy(int8_t xvelocity){
    uint8_t i, j;
    // Fill enemy array with xvel and yvel values
    for( i = 0; i < ENEMY_ROW; i++ ){
        for( j = 0; j < ENEMY_COLUMN; j++ ){
            Enemies[i][j].xvel = xvelocity;
        }
    }
}




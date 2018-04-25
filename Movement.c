// Movement.c


#include <stdint.h>
#include "adc.h"
#include "level.h"
#include "DisplayMap.h"

extern uint16_t Buffer1[DISPLAY_HEIGHT][DISPLAY_WIDTH];

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
    
   
void Move(sprite_t* object){
    if( ((object -> x + object -> xvel) > 0) && ((object -> x + object -> xvel) < DISPLAY_WIDTH) ){
        (object -> x) = (object -> x) + (object -> xvel);
    }
//    if( ((object -> y + object -> yvel) > 0) && ((object -> y + object -> yvel) < DISPLAY_HEIGHT) ){
 //       object -> y = object -> y + object -> yvel;
//    }
    DrawImage_Buffer(object, Buffer1);
}

/*
extern flag_t MoveStatus;
extern movestate_t CurrentMove;
extern player_t Player1;
extern enemy_t Enemies[2][6];


void Move_Player(){
    while(MoveStatus == BUSY){}
    // acknowledge new ADC input
    MoveStatus = BUSY;

    switch(CurrentMove){
        case LEFT:
            if( Player1.x == 0 ){
                break;
            }
            Player1.x -=2;
            break;
        case RIGHT:
            if( Player1.x == DISPLAY_WIDTH ){
                break;
            }
            Player1.x +=2;
            break;
        case HOLD:
            break;
    }
}


void Move_Enemy(){
    uint8_t i, j;
    int8_t direction; 
    if(Enemies[1][1].x <= 0){
        direction = 1; 
    }
    else if((Enemies[1][5].x + Enemies[1][5].w) >= DISPLAY_WIDTH){
        direction = -1;
    }
    for( i = 0; i < 2; i++ ){
        for( j = 0; j < 6; j++ ){
            Enemies[i][j].x += direction; 
        }
    }
}
*/


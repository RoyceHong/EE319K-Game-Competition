// Movement.c


#include <stdint.h>
#include "adc.h"
#include "level.h"
#include "DisplayMap.h"

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



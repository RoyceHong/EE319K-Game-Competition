// Movement.c


#include <stdint.h>
#include "movement.h"
#include "adc.h"
#include "DisplayMap.h"
#include "ST7735.h"


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


// Universal move function, takes sprite as input and moves according to xvel
void MoveX(sprite_t* object){
    if( ((object -> x + object -> xvel) >= 0) && ((object -> x + object -> xvel + object -> w) <= DISPLAY_WIDTH) ){
        (object -> x) = (object -> x) + (object -> xvel);
    }
    if(object -> life == ALIVE){
        ST7735_DrawBitmap(object -> x, object -> y, object -> image, object -> w, object -> h);
    }
}


// Universal move function, takes sprite as input and moves according to yvel
void MoveY(sprite_t* object){
    if( ((object -> y + object -> yvel) >= 0) && ((object -> y + object -> yvel + object -> h) <= DISPLAY_HEIGHT) ){
        object -> y = object -> y + object -> yvel;
    }
    if(object -> life == ALIVE){
        ST7735_DrawBitmap(object -> x, object -> y, object -> image, object -> w, object -> h);
    }
}







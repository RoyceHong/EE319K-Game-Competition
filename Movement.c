// Movement.c


#include <stdint.h>
#include "movement.h"
#include "adc.h"
#include "level.h"
#include "DisplayMap.h"
#include "ST7735.h"

//extern uint16_t Buffer1[DISPLAY_HEIGHT][DISPLAY_WIDTH];

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


// FOR DEBUGGING PURPOSES
void Move(sprite_t* object){
    if( ((object -> x + object -> xvel) > 0) && ((object -> x + object -> xvel) < DISPLAY_WIDTH) ){
        (object -> x) = (object -> x) + (object -> xvel);
    }
    if( ((object -> y + object -> yvel) > 0) && ((object -> y + object -> yvel) < DISPLAY_HEIGHT) ){
        object -> y = object -> y + object -> yvel;
    }
    ST7735_DrawBitmap(object -> x, object -> y, object -> image, object -> w, object -> h);
}



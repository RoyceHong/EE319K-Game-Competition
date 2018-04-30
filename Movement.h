// Movement.h 

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "adc.h"
#include "player.h"


// Takes direction input and adjusts velocities for player accordingly 
void Process_Move(sprite_t *player, movestate_t direction);


// Universal move function that moves a given sprite in the horizontal direction
void MoveX(sprite_t *object);


// Universal move function that moves a given sprite in the vertical direction
void MoveY(sprite_t *object);


#endif


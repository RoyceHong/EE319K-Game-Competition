// Movement.h 

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "adc.h"
#include "level.h"

// enum defining direction the enemy is moving 
typedef enum {X, Y} enemdir_t;


// Takes direction input and adjusts velocities for player accordingly 
void Process_Move(sprite_t *player, movestate_t xdirection);


// Universal move function that moves a given sprite in the horizontal direction
void MoveX(sprite_t *object);


// Universal move function that moves a given sprite in the vertical direction
void MoveY(sprite_t *object);


// Manipulates the velocities of all enemies and calls Move
void Move_Enemy(enemdir_t);


// Sets all enemy velocities to the input velocity
// Used when an alien has hit the edge of the screen and needs to go the opposite direction
void Fill_Enemy(int8_t velocity);


#endif


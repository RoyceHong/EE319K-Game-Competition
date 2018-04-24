// Level.h
// Creates the position 

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>


// enum indicating player dead or alive status 
typedef enum {DEAD, ALIVE} status_t;


// Player structure
// Defines position, size, and status of the player
typedef struct player_t{
    int16_t x;
    int16_t y;
    const uint16_t *image;
    int16_t w;
    int16_t h;
    status_t life; 
} player_t ; 


// Enemy structure
// Defines position, size, and status of the the enemy
typedef struct enemy_t{
    int16_t x;
    int16_t y;
    const uint16_t *image;
    int16_t w;
    int16_t h;
    status_t life; 
} enemy_t; 


// Initializes all players and enemies 
// Called at the beginning of the game 
void Level_Init(void);


#endif

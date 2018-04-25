// Level.h
// Creates the position 

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>


// enum indicating player dead or alive status 
typedef enum {DEAD, ALIVE} status_t;


// Universal sprite structure
// specifies location, image, movement velocity, and life status
typedef struct sprite_t{
    int16_t x;
    int16_t y;
    const uint16_t *image;
    int16_t w;
    int16_t h;
    int16_t xvel;
    int16_t yvel;
    status_t life;
}sprite_t;


// Initializes all players and enemies 
// Called at the beginning of the game 
void Level_Init(void);


#endif

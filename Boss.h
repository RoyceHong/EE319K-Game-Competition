// Boss.h
// Contains all information on bosses encountered during the bullet hell portion of the game 

#ifndef BOSS_H
#define BOSS_H

#include <stdint.h>
#include "player.h"

// Boss structure  
typedef struct boss_t {
    int16_t x;
    int16_t y;
    const uint16_t *image;
    int16_t w;
    int16_t h;
    int16_t xvel;
    int16_t yvel;
    status_t life;
    uint32_t health;
}boss_t;


// Draws the boss on the screen 
void Boss_Init(uint8_t stage);


void Boss_Move(void);


#endif


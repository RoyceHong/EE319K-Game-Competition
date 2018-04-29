// Boss.h
// Contains all information on bosses encountered during the bullet hell portion of the game 

#ifndef BOSS_H
#define BOSS_H

#include <stdint.h>
#include "player.h"

#ifndef BOSS1_ATTACKNUM
#define BOSS1_ATTACKNUM 3
#endif


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


typedef struct velocity_t{
    int16_t vx;
    int16_t vy;
}velocity_t;
    

typedef struct atkpattern_t {
    uint16_t numBullets;
    velocity_t* velocity;
    uint16_t numStates;
//    uint16_t color;
    uint32_t bulletSpeed;
//    uint32_t bulletSpeedCurrent;
    uint32_t BossTriggerCount;
//    uint32_t BossTriggerCountCurrent;
}atkpattern_t;
    


// Draws the boss on the screen 
void Boss_Init(uint8_t stage);


// outputs a random attack from the bosses attacks array
atkpattern_t ChooseRandAttack(void);


void Color_Init(void);


uint16_t ChooseRandColor(void);


#endif


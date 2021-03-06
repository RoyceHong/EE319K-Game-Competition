// Boss.h
// Contains all information on bosses encountered during the bullet hell portion of the game 

#ifndef BOSS_H
#define BOSS_H

#include <stdint.h>
#include "player.h"

#ifndef BOSS1_ATTACKNUM
#define BOSS1_ATTACKNUM 3
#endif

#ifndef BOSS2_ATTACKNUM
#define BOSS2_ATTACKNUM 5
#endif

#ifndef BOSS3_ATTACKNUM
#define BOSS3_ATTACKNUM 8
#endif

#ifndef BOSSMOVE_TIMER
#define BOSSMOVE_TIMER 4500
#endif

#ifndef BOSS_X
#define BOSS_X 54
#endif

#ifndef BOSS_Y
#define BOSS_Y 60
#endif

#ifndef BOSS1_HEALTH
#define BOSS1_HEALTH 350
#endif

#ifndef BOSS2_HEALTH
#define BOSS2_HEALTH 300
#endif

#ifndef BOSS3_HEALTH
#define BOSS3_HEALTH 400
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
    uint8_t attackNum;
}boss_t;


typedef const struct velocity_t{
    int16_t vx;
    int16_t vy;
}velocity_t;
    

typedef struct atkpattern_t {
    uint8_t attackNum;
    uint16_t numBullets;
    velocity_t* velocity;
    uint16_t numStates;
    uint16_t color;
    uint32_t bulletSpeed;
    uint32_t BossTriggerCount;
    uint16_t repeatVal;
}atkpattern_t;
    


// Draws the boss on the screen 
void Boss_Init(uint8_t bossNumber);


// outputs a random attack from the bosses attacks array
uint8_t ChooseRandAttack(void);


// initializes colors of each of the attack patterns
void Color_Init(void);


// Moves the boss horizontall across the screen 
void Move_Boss(void);


// changes x, y coordinates of the boss
void MoveBoss(boss_t* object);


#endif


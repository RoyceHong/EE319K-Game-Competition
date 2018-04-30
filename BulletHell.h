// BulletHell.h

#ifndef BULLETHELL_H
#define BULLETHELL_H

#include <stdint.h>
#include "bullet.h"
#include "Boss.h"


#ifndef BULLETHELL_PTRIGGER
#define BULLETHELL_PTRIGGER 4000
#endif

#ifndef BULLETNUM_HELL
#define BULLETNUM_HELL 300
#endif

#ifndef HELLBULLETSPEEDP
#define HELLBULLETSPEEDP 250
#endif


// bullet structure 
typedef struct bossbullet_t{
    int16_t x;
    int16_t y;
    int8_t xvel;
    int8_t yvel;
    int8_t w;
    int8_t h;
    uint16_t color;
} bossbullet_t;

// initializes all boss bullets to black
void BossBullet_Init(void);
    

// main function to manipulate player bullets during bullet hell game 
void PlayerBulletHell(void);


// check if player bullets have hit the boss
void checkBulletBoss(bullet_t* Shot);


// check the hitbox of the Boss
contact_t BossBoxCheck(bullet_t* bullet, boss_t* object);


// creates bullets for the enemy 
uint8_t createBossBullet(fireBullet_t Condition, uint8_t bossNumber, atkpattern_t pattern);


// main function that manipulates bullets for boss
void BossBullet(void);






#endif


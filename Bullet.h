// Bullet.h

#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include "Player.h"

#ifndef BULLETNUM_INVADER
#define BULLETNUM_INVADER 4
#endif

#ifndef BLACK
#define BLACK       0x0000
#endif

#ifndef MAX_BULLET
#define MAX_BULLET         100
#endif

#ifndef TRIGGERCOUNTER
#define TRIGGERCOUNTER    300000
#endif

#ifndef TRIGGERCOUNTERPLAYER
#define TRIGGERCOUNTERPLAYER       80000
#endif

#ifndef GREEN
#define GREEN       0x07E0
#endif

#ifndef BULLETSPEED
#define BULLETSPEED  5000
#endif


typedef struct bullet_t{
    int16_t x;
    int16_t y;
    int8_t xvel;
    int8_t yvel;
    int8_t w;
    int8_t h;
    uint16_t color;
} bullet_t;

typedef enum {FIRE, NO_FIRE} fireBullet_t;

typedef enum {CONTACT, NO_CONTACT} contact_t;

void Bullet_Init(void);

sprite_t *enemyAttack(void);

uint8_t createBullet(fireBullet_t Condition);

uint8_t createEnemyBullet(fireBullet_t Condition, sprite_t *Enemy);

void checkBulletEnemy(bullet_t* Shot);

void checkBulletEdge(bullet_t* Shot);

contact_t hitBoxCheck(bullet_t* bullet, sprite_t* object);

contact_t edgeCheck(bullet_t* bullet);

void moveBullet(bullet_t* bullet);

void BulletMain(void);

fireBullet_t checkButton(void);

#endif

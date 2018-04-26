// Bullet.h

#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include "Level.h"


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

uint8_t createBullet(fireBullet_t Condition);
void checkBulletEnemy(bullet_t* Shot);
void checkBulletEdge(bullet_t* Shot);
contact_t hitBoxCheck(bullet_t bullet, sprite_t object);
contact_t edgeCheck(bullet_t bullet);
void moveBullet(bullet_t *bullet);

void BulletMain(void);

#endif

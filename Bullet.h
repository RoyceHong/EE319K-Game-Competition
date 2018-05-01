// Bullet.h

#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include "Player.h"

#ifndef BULLETNUM_INVADER
#define BULLETNUM_INVADER 4
#endif

#ifndef PLAYER_BULLETNUM
#define PLAYER_BULLETNUM 50
#endif

#ifndef BLACK
#define BLACK 0x0000
#endif

#ifndef GREEN
#define GREEN 0x07E0
#endif

#ifndef TRIGGERCOUNTERENEMY
#define TRIGGERCOUNTERENEMY 72000
#endif

#ifndef TRIGGERCOUNTERPLAYER
#define TRIGGERCOUNTERPLAYER 42000
#endif


#ifndef ENEMYBULLETSPEED
#define ENEMYBULLETSPEED 1500
#endif

#ifndef BULLETSPEEDP
#define BULLETSPEEDP 2000
#endif


// bullet structure 
typedef struct bullet_t{
    int16_t x;
    int16_t y;
    int16_t xvel;
    int16_t xvelSum;
    int16_t yvel;
    int16_t yvelSum;
    int8_t w;
    int8_t h;
    uint16_t color;
} bullet_t;


// enum determining whether bullet should be fired or not
typedef enum {FIRE, NO_FIRE} fireBullet_t;

// enum determining whether bullet has contacted something or not
typedef enum {CONTACT, NO_CONTACT} contact_t;


// initializes all bullets in bullet array to black 
void Bullet_Init(void);


// chooses a random enemy in the enemy array to attack 
sprite_t *enemyAttack(void);


// creates bullets for the player 
uint8_t createBullet(fireBullet_t Condition, uint16_t BulletNum, sprite_t* player);


// creates bullets for the enemy 
uint8_t createEnemyBullet(fireBullet_t Condition, sprite_t *Enemy);


// check if player has been hit by a bullet 
void checkBulletPlayer(bullet_t* Shot, sprite_t* player);


// check if enemy has been hit by a bullet
void checkBulletEnemy(bullet_t* Shot);


// check if bullets have reached the edge of the screen 
void checkBulletEdge(bullet_t* Shot);


// check if bullets have hit the bunker (Space Invaders)
void checkBulletObstacle(bullet_t* Shot);


// universal collision detection function
contact_t hitBoxCheck(bullet_t* bullet, sprite_t* object);


// universal edge detection function
contact_t edgeCheck(bullet_t* bullet);

// absolute value function
int16_t abs(int16_t num);


// Moves bullets
void moveBullet(bullet_t* bullet);


// Main function in charge of manipulating the player bullets
void PlayerBullet(void);


// Main function in charge of manipulating enemy bullets (Space Invaders)
void EnemyBullet(void);


// checks if the button has been pressed 
fireBullet_t checkButton(void);


#endif

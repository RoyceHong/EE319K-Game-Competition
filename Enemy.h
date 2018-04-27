// Enemy.h 
// Contains all information about the enemies 

#ifndef ENEMY_H
#define ENEMY_H

#include <stdint.h>

#ifndef ENEMY_ROW
#define ENEMY_ROW 4
#endif

#ifndef ENEMY_COLUMN
#define ENEMY_COLUMN 6
#endif

#ifndef ENEMY_XTIMER
#define ENEMY_XTIMER 10000
#endif

// Initialize enemies on the screen 
void Enemy_Init(void);


// Manipulates the velocities of all enemies and calls Move
void Move_Enemy(void);


// Sets all enemy velocities to the input velocity
// Used when an alien has hit the edge of the screen and needs to go the opposite direction
void Fill_Enemy(int8_t velocity);

#endif

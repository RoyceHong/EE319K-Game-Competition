// Enemy.h 
// Contains all information about the enemies 

#ifndef ENEMY_H
#define ENEMY_H

#include <stdint.h>

#ifndef ENEMY_ROW
#define ENEMY_ROW 1
#endif

#ifndef ENEMY_COLUMN
#define ENEMY_COLUMN 5
#endif

#ifndef ENEMY_XTIMER
#define ENEMY_XTIMER 10000
#endif

#ifndef OBSTACLE_SIZE
#define OBSTACLE_SIZE 2
#endif

// Initialize enemies on the screen 
void Enemy_Init(void);


// Manipulates the velocities of all enemies and calls Move
void Move_Enemy(void);


// Sets all enemy velocities to the input velocity
// Used when an alien has hit the edge of the screen and needs to go the opposite direction
void Fill_Enemy(int8_t velocity);


// Function that checks if all the enemies are dead
void Enemy_Dead(void);


void Bunker_Init(void);

#endif

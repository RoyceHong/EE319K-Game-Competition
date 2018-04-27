// Player.h 
// Contains all information regarding the player 


#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

// *************************** Sprite Structure *************************************** // 
// enum indicating object dead or alive 
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


// Initially draw player on the screen 
void Player_Init(void);


// Move the player 
void Move_Player(void);


#endif

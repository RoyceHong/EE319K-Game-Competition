// Player.c

#include <stdint.h>
#include "Player.h"
#include "Movement.h"
#include "ST7735.h"
#include "sprites.h"

extern uint8_t spaceInvadersRestriction;
extern const uint16_t PlayerRightFrame_1[];
// Player1 initial definition 
sprite_t Player1 = {52,  159,  PlayerRightFrame_1,  16, 11, 0, 0, ALIVE};

// flag that detects when player should be moved
extern uint8_t playerflag;

// Draws the player on the screen
void Player_Init(){
    // Draw player on screen
    ST7735_DrawBitmap(Player1.x, Player1.y, Player1.image, Player1.w,  Player1.h);
    Player1.life = ALIVE;
}

// Moves the player 
void Move_Player(){
     // loop that controls the rate at which player moves
    if(playerflag == 1){
        MoveX(&Player1);
        if(spaceInvadersRestriction == 0){
            MoveY(&Player1);
        }
        playerflag = 0;
    }
}





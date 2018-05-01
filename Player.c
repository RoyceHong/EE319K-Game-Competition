// Player.c

#include <stdint.h>
#include "Player.h"
#include "Movement.h"
#include "ST7735.h"
#include "sprites.h"

extern uint8_t spaceInvadersRestriction;
extern const uint16_t PlayerRightFrame_1[];
extern const uint16_t PlayerShip2[];
// Player1 initial definition 
sprite_t Player1 = {52,  159,  PlayerRightFrame_1,  16, 11, 0, 0, ALIVE};
sprite_t PlayerHell = {48, 159, PlayerShip2, 17, 12, 0, 0, ALIVE};

// flag that detects when player should be moved
extern uint8_t playerflag;

// Draws the player on the screen
void Player_Init(){
    // Draw player on screen
    Player1.life = ALIVE;
    Player1.x = 52;
    Player1.y = 159;
    ST7735_DrawBitmap(Player1.x, Player1.y, Player1.image, Player1.w,  Player1.h);
}


void PlayerHell_Init(){
    PlayerHell.life = ALIVE;
    PlayerHell.x = 48;
    PlayerHell.y = 159;
    ST7735_DrawBitmap(PlayerHell.x, PlayerHell.y, PlayerHell.image, PlayerHell.w,  PlayerHell.h);
}


// Moves the player 
void Move_Player(){
     // loop that controls the rate at which player moves
    if(playerflag == 1){
        MoveX(&Player1);
        playerflag = 0;
    }
}


// Moves the player 
void MoveHell_Player(){
     // loop that controls the rate at which player moves
    if(playerflag == 1){
        MoveX(&PlayerHell);
        MoveY(&PlayerHell);
        playerflag = 0;
    }
}





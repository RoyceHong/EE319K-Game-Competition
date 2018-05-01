//BattleSelect.c
#include <stdint.h>
#include "BattleSelect.h"
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "Systick.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "MainMenu.h"
#include "Button.h"
#include "DisplayMap.h"
#include "MainMenu.h" 
#include "Boss.h"
#include "BulletHell.h"
#include "CutScene.h"
#include "Sound.h"

void Delay100ms(uint32_t count);

extern uint8_t GameOn;
// determines what stage of the bullet hell the player is on
extern uint8_t bossNum;
// holds SUCCESS, FAIL, or IN_PROGRESS
progress_t gameProgress;
// variable indicating space invaders horizontal restriction
uint8_t spaceInvadersRestriction = 1;
extern uint8_t buttonStatus;


void BattleStartInit(void){
    // Bullet hell initializations 
    // allow vertical movement for bullet hell portion of game 
    spaceInvadersRestriction = 0;
    // fill screen black
    ST7735_FillScreen(0x0000);
    // disable edge interrupts for bullet hell portion of game
    DisableEdgeInt();
    PlayerHell_Init();
    Boss_Init(bossNum);
    Bullet_Init();
    BossBullet_Init();
    Color_Init();
}


void BattleStart(void){
    // ************************************ BULLET HELL *********************************************** 
    while(GameOn == 1 && gameProgress == IN_PROGRESS){
        MoveHell_Player();
        Move_Boss();
        BossBullet();
        PlayerBulletHell();
    }
// ************************************ END BULLET HELL ********************************************
    
    
}

void SpaceInvadersInit(void){
    // Initializations required for space invaders portion of the game 
    spaceInvadersRestriction = 1;
    Bullet_Init();
    // Make screen blank 
    ST7735_FillScreen(0x0000);
    Player_Init();
    Bunker_Init();
    Enemy_Init();
    // acknowledge button press and reset it 
    buttonStatus = 0;
}


void SpaceInvaders(void){
    // ************************************ SPACE INVADERS ******************************************* 
    
    while(GameOn == 1 && gameProgress == IN_PROGRESS){ 
        PlayerBullet();
        EnemyBullet();
        Move_Player();
        Move_Enemy();
        Enemy_Dead();
    }
    ST7735_FillRect(0, 0 , DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    Delay100ms(8);
    
// ************************************ END SPACE INVADERS **************************************** 
}




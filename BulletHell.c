// BulletHell.c

#include <stdint.h>
#include "BulletHell.h"
#include "Boss.h" 
#include "Bullet.h"
#include "Button.h"
#include "ST7735.h"
#include "MainMenu.h"

extern progress_t gameProgress;
extern sprite_t Player1;
extern bullet_t PlayerBullets[MAX_BULLET];
extern fireBullet_t Trigger;
extern uint8_t bossNum;
// array containing all the bosses 
extern boss_t Bosses[];

uint32_t HellTrigger = 0;


// universal collision detection function
contact_t BossBoxCheck(bullet_t* bullet, boss_t* object){
    if( ((bullet -> x >= object -> x) && (bullet -> x <= (object -> x + object -> w - 1)) )
        && ((bullet -> y <= object -> y) && (bullet -> y >= (object -> y - object -> h - 2)) )){ 
           return CONTACT;
    }
    else{
           return NO_CONTACT;
    }
 }

// checks if boss has been killed by player 
void checkBulletBoss(bullet_t* Shot){
    contact_t BulletStatus;
    if(Bosses[bossNum].life == ALIVE && (*Shot).color != BLACK){
       BulletStatus = BossBoxCheck(Shot , &Bosses[bossNum]);
        if(BulletStatus == CONTACT){
            Bosses[bossNum].health--;
            if(Bosses[bossNum].health == 0){
                Bosses[bossNum].life = DEAD;
                // game progresses to next section by death of boss
                // status is SUCCESS
                gameProgress = SUCCESS;
            }
            (*Shot).color = BLACK;
            uint16_t FillColor = BLACK;
            ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, FillColor); 
        }
    }
}


// main function in charge of manipulating the player bullets
void PlayerBulletHell(void){
    static uint32_t bulletSpeed = BULLETSPEED;
    uint8_t button = Button_In();    
    if(HellTrigger > 0){
        HellTrigger --;
    }
    Trigger = NO_FIRE;
    
    if(HellTrigger <= 1){
        if(button != 0){
            Trigger = FIRE;
        }
        if(Trigger == FIRE){
            HellTrigger = BULLETHELL_TRIGGER;
        }
    }
    createBullet(Trigger, BULLETNUM_HELL); 
    
    if(bulletSpeed == 0){
        bulletSpeed = BULLETSPEED;
        for(uint32_t i = 0; i < BULLETNUM_HELL; i++){
            // manipulate player bullets
            checkBulletBoss(&(PlayerBullets[i]));
            checkBulletEdge(&(PlayerBullets[i]));
            moveBullet(&(PlayerBullets[i]));
        }
    }
    bulletSpeed--;
}




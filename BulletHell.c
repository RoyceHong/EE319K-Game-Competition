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
extern atkpattern_t Boss1[];

// attack patterns
extern atkpattern_t ConeVertical;
extern atkpattern_t CircleBlast;
extern atkpattern_t Beam;


bullet_t BossBullets[MAX_BULLET];
fireBullet_t TriggerBoss;
uint32_t TriggerCountBoss = 0;
uint32_t HellTrigger = 0;
uint32_t BossBulletCount = 0;
atkpattern_t attack;



// initializes boss bullets in bullet array to black  
void BossBullet_Init(void){
    for(uint32_t i = 0; i < MAX_BULLET; i++){
        BossBullets[i].color = BLACK;
    }
}


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
    static uint32_t bulletSpeed = HELLBULLETSPEEDP;
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
        bulletSpeed = HELLBULLETSPEEDP;
        for(uint32_t i = 0; i < BULLETNUM_HELL; i++){
            // manipulate player bullets
            checkBulletBoss(&(PlayerBullets[i]));
            checkBulletEdge(&(PlayerBullets[i]));
            moveBullet(&(PlayerBullets[i]));
        }
    }
    bulletSpeed--;
}


uint16_t bossShotState = 0; 

// creates bullets for the boss
uint8_t createBossBullet(fireBullet_t Condition, uint8_t bossNumber, atkpattern_t pattern){
    if(Condition == FIRE){
        uint32_t i = 0;
        while(BossBullets[BossBulletCount].color != BLACK){
            BossBulletCount ++;
            BossBulletCount = BossBulletCount % BULLETNUM_HELL;
            if(i >= BULLETNUM_HELL){
                return 0;
            }
            i++; 
        }
        for(uint32_t j = 0; j < pattern.numBullets; j++){
            BossBullets[BossBulletCount + j].h = 4;
            BossBullets[BossBulletCount + j].w = 4;
            BossBullets[BossBulletCount + j].x = Bosses[bossNumber].x + (Bosses[bossNumber].w/2 - 2);
            BossBullets[BossBulletCount + j].y = Bosses[bossNumber].y;
            BossBullets[BossBulletCount + j].xvel = pattern.velocity[bossShotState].vx;
            BossBullets[BossBulletCount + j].xvelSum = 0;
            BossBullets[BossBulletCount + j].yvelSum = 0;
            BossBullets[BossBulletCount + j].yvel = pattern.velocity[bossShotState].vy;
            BossBullets[BossBulletCount + j].color = pattern.color;
            bossShotState++;
            bossShotState = bossShotState % pattern.numStates;
        }
    }
    return 1;
}


// main function in charge of manipulating the boss bullets
void BossBullet(void){
    // chooses a random attack from the bosses attack array
    if(bossShotState == 0){      
        attack = ChooseRandAttack();
    }
    
    // bulletSpeed determines how fast bullet travels on screen 
    static uint32_t BossBulletSpeed = BOSS_BULLET_SPEED; 
    if(TriggerCountBoss > 0){
        TriggerCountBoss --;
    }
    
    TriggerBoss = NO_FIRE;
    
    if(TriggerCountBoss <= 1){
        TriggerCountBoss = attack.BossTriggerCount;
        TriggerBoss = FIRE;
    }
    
    createBossBullet(TriggerBoss, bossNum, attack);   
    
    if(BossBulletSpeed == 0){
        BossBulletSpeed = BOSS_BULLET_SPEED;
        for(uint32_t i = 0; i < BULLETNUM_HELL; i++){
            // manipulate enemy bullets 
            checkBulletPlayer(&(BossBullets[i]));
            checkBulletEdge(&(BossBullets[i]));
            moveBullet(&(BossBullets[i]));
        }
    }
    BossBulletSpeed--;
}






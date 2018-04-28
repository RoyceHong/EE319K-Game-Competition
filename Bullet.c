// Bullet.c


#include <stdint.h>
#include "Bullet.h"
#include "ST7735.h"
#include "DisplayMap.h"
#include "enemy.h"
#include "tm4c123gh6pm.h"
#include "Button.h"
#include "MainMenu.h"

void Random_Init(uint32_t);
uint32_t Random(void);
extern sprite_t Player1;
extern sprite_t Enemies[ENEMY_ROW][ENEMY_COLUMN];
extern sprite_t Bunkers[OBSTACLE_SIZE];
extern uint8_t buttonStatus;
extern progress_t gameProgress;

bullet_t PlayerBullets[MAX_BULLET];
bullet_t EnemyBullets[MAX_BULLET];
fireBullet_t Trigger;


uint8_t BulletCount = 0;
uint32_t bulletSpeed = BULLETSPEED;

void Bullet_Init(void){
    for(uint32_t i = 0; i < MAX_BULLET; i++){
        PlayerBullets[i].color = BLACK;
        EnemyBullets[i].color = BLACK;
    }
}

sprite_t *enemyAttack(void){

    int16_t HighestRow[ENEMY_COLUMN];
    for(uint16_t i = 0; i < ENEMY_COLUMN; i++){
        HighestRow[i] = -1;
    }
    for(uint16_t i = 0; i < ENEMY_ROW; i++){
        for(uint16_t j = 0; j < ENEMY_COLUMN; j++){
            // Find highest row in each column
            if(Enemies[i][j].life == ALIVE){
                HighestRow[j] = i;
            }
        }
    }
    uint32_t Column = (Random() % ENEMY_COLUMN);
    
   if(HighestRow[Column] != -1){
        return 	&(Enemies[HighestRow[Column]][Column]);
    }
   else{
       return 0;
   }
}

uint8_t createBullet(fireBullet_t Condition){
    if(Condition == FIRE){
        uint32_t i = 0;
        while(PlayerBullets[BulletCount].color != BLACK){
            BulletCount ++;
            BulletCount = BulletCount % BULLETNUM_INVADER;
            if(i >= BULLETNUM_INVADER){
                    return 0;
            }
            i++; 
        }
            
        PlayerBullets[BulletCount].h = 2;
        PlayerBullets[BulletCount].w = 2;
        PlayerBullets[BulletCount].x = Player1.x + (Player1.w/2) -1;
        PlayerBullets[BulletCount].y = Player1.y - (Player1.h) - 1;
        PlayerBullets[BulletCount].xvel = 0;
        PlayerBullets[BulletCount].yvel = -4;
        PlayerBullets[BulletCount].color = 0xFFFF; 
    }
    return 1;
}


uint16_t EnemyBulletCount;

uint8_t createEnemyBullet(fireBullet_t Condition, sprite_t *Enemy){
    if(Condition == FIRE && Enemy != 0){
        uint32_t i = 0;
        while(EnemyBullets[EnemyBulletCount].color != BLACK){
            EnemyBulletCount ++;
            EnemyBulletCount = EnemyBulletCount % BULLETNUM_INVADER;
            if(i >= BULLETNUM_INVADER){
                    return 0;
            }
            i++; 
        }
                
            EnemyBullets[EnemyBulletCount].h = 3;
            EnemyBullets[EnemyBulletCount].w = 2;
            EnemyBullets[EnemyBulletCount].x = Enemy->x + (Enemy->w/2) - 1;
            EnemyBullets[EnemyBulletCount].y = Enemy->y;
            EnemyBullets[EnemyBulletCount].xvel = 0;
            EnemyBullets[EnemyBulletCount].yvel = 2;
            EnemyBullets[EnemyBulletCount].color = 0x07E0; 
        }
        return 1;
}

void checkBulletPlayer(bullet_t* Shot){
    contact_t BulletStatus;
    if(Player1.life == ALIVE && (*Shot).color != BLACK){
       BulletStatus = hitBoxCheck(Shot , &Player1);
        if(BulletStatus == CONTACT){
            Player1.life = DEAD;
            // game progresses to next section by death of player
            // status is FAIL
            gameProgress = FAIL;
            // Additional Animation should be added here
            (*Shot).color = BLACK;
            uint16_t FillColor = BLACK;
            ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, FillColor); 
        }
    }
}




void checkBulletEnemy(bullet_t* Shot){
    contact_t BulletStatus;
    if((*Shot).color != BLACK){
        for(uint16_t i = 0; i < ENEMY_ROW; i++){
            for(uint16_t j = 0; j < ENEMY_COLUMN; j++){
                if(Enemies[i][j].life == ALIVE){
                   BulletStatus = hitBoxCheck(Shot , &Enemies[i][j]);
                    if(BulletStatus == CONTACT){
                        Enemies[i][j].life = DEAD;
                        ST7735_FillRect(Enemies[i][j].x, Enemies[i][j].y - Enemies[i][j].h , Enemies[i][j].w, Enemies[i][j].h, BLACK);
                        // Additional Animation should be added here
                        (*Shot).color = BLACK;
                        uint16_t FillColor = BLACK;
                        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, FillColor); 
                    }
                }
            }
        }
    }
}

void checkBulletEdge(bullet_t* Shot){
    contact_t BulletStatus;
    BulletStatus = edgeCheck(Shot);
    if(BulletStatus == CONTACT){
        // Additional Animation should be added here
        (*Shot).color = BLACK; 
        uint16_t FillColor = BLACK;
        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, FillColor);        
            
    }
}


void checkBulletObstacle(bullet_t* Shot){
    contact_t BulletStatus;
    for(uint16_t i = 0; i < OBSTACLE_SIZE; i++){
        if(Bunkers[i].life == ALIVE){
           BulletStatus = hitBoxCheck(Shot , &Bunkers[i]);
           if(BulletStatus == CONTACT){
                // Additional Animation should be added here
                (*Shot).color = BLACK;
                uint16_t FillColor = BLACK;
                ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, FillColor); 
           }
        }
    }
}
            
            
contact_t hitBoxCheck(bullet_t* bullet, sprite_t* object){
    if( ((bullet -> x >= object -> x) && (bullet -> x <= (object -> x + object -> w - 1)) )
        && ((bullet -> y <= object -> y) && (bullet -> y >= (object -> y - object -> h - 2)) )){ 
           return CONTACT;
    }
    else{
           return NO_CONTACT;
    }
 }

contact_t edgeCheck(bullet_t* bullet){ 
     if( (bullet -> x <= 1) || (bullet -> x >= (DISPLAY_WIDTH - 1)) 
        || (bullet -> y <= 1) || (bullet -> y >= (DISPLAY_HEIGHT - 1)) ){
            
            return CONTACT;
     }
     else{
           return NO_CONTACT;
     }
}


void moveBullet(bullet_t *Shot){
    if((*Shot).color != BLACK){
        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, BLACK);
        // Update Bullet Coordinates
        (*Shot).x = (*Shot).x + (*Shot).xvel;
        (*Shot).y = (*Shot).y + (*Shot).yvel;
        // New Bullet
        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, (*Shot).color);
    }
}

uint32_t TriggerCount = TRIGGERCOUNTER;
uint32_t TriggerCountPlayer = 0;
fireBullet_t TriggerEnemy;

void BulletMain(void){  // Later add input asking for max number of bullets
    if(TriggerCountPlayer > 0){
        TriggerCountPlayer --;
    }
    TriggerCount --;
    Trigger = NO_FIRE;
    TriggerEnemy = NO_FIRE;
    if(TriggerCount <= 1){
        TriggerCount = TRIGGERCOUNTER;
        TriggerEnemy = FIRE;
    }
    if(TriggerCountPlayer <= 1){
        Trigger = checkButton();
        if(Trigger == FIRE){
            TriggerCountPlayer = TRIGGERCOUNTERPLAYER;
        }
    }
    createBullet(Trigger); 
   createEnemyBullet(TriggerEnemy, enemyAttack());   
    if(bulletSpeed == 0){
        bulletSpeed = BULLETSPEED;
        for(uint32_t i = 0; i < BULLETNUM_INVADER; i++){
            checkBulletEnemy(&(PlayerBullets[i]));
            checkBulletObstacle(&(PlayerBullets[i]));
            checkBulletEdge(&(PlayerBullets[i]));
            moveBullet(&(PlayerBullets[i]));
            
            checkBulletPlayer(&(EnemyBullets[i]));
            checkBulletObstacle(&(EnemyBullets[i]));
            checkBulletEdge(&(EnemyBullets[i]));
            moveBullet(&(EnemyBullets[i]));
        }
    }
    bulletSpeed--;
}


fireBullet_t checkButton(void){
    if(buttonStatus == 1){
        // acknowledge button press
        buttonStatus = 0;
        return FIRE;
    }
    else{
        return NO_FIRE;
    }
}
        
        
    
    
        


        
    
        
        



// Bullet.c


#include <stdint.h>
#include "Bullet.h"
#include "ST7735.h"
#include "DisplayMap.h"
#include "enemy.h"


extern sprite_t Player1;
extern sprite_t Enemies[ENEMY_ROW][ENEMY_COLUMN];

bullet_t PlayerBullets[MAX_BULLET];
bullet_t BossBullets[MAX_BULLET];
fireBullet_t Trigger;


uint8_t BulletCount = 0;

void Bullet_Init(void){
    for(uint32_t i = 0; i < MAX_BULLET; i++){
        PlayerBullets[i].color = BLACK;
        BossBullets[i].color = BLACK;
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
        PlayerBullets[BulletCount].yvel = -2;
        PlayerBullets[BulletCount].color = 0xFFFF; 
    }
    return 1;
}

void checkBulletEnemy(bullet_t* Shot){
    contact_t BulletStatus;
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

/*      
void checkBulletObstacle(bullet_t* Shot){
    contact_t BulletStatus;
    for(uint16_t i = 0; i < OBSTACLE_ROW; i++){
        for(uint16_t j = 0; j < OBSTACLE_COLUMN; j++){
           BulletStatus = hitBoxCheck(*Shot , Obstacle[i][j]);
            if(BulletStatus == CONTACT){
                uint16_t FillColor = BLACK;
                ST7735_FillRect(Obstacle[i][j].x, Obstacle[i][j].y, Obstacle[i][j].w, Obstacle[i][j].h, FillColor);
                // Additional Animation should be added here
                (*Shot).color = BLACK;
            }
        }
    }
} 
*/



            
            
contact_t hitBoxCheck(bullet_t* bullet, sprite_t* object){
    if( ((bullet -> x >= object -> x) && (bullet -> x <= (object -> x + object -> w - 1)) )
        && ((bullet -> y <= object -> y) && (bullet -> y >= (object -> y - object -> h + 1)) )){ 
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

uint32_t bulletnum = 200000;

void moveBullet(bullet_t *Shot){
    if((*Shot).color != BLACK){
        uint16_t FillColor = BLACK;
        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, FillColor);
        // Update Bullet Coordinates
        (*Shot).x = (*Shot).x + (*Shot).xvel;
        (*Shot).y = (*Shot).y + (*Shot).yvel;
        // New Bullet
        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, (*Shot).color);
    }
}

uint32_t TriggerCount = TRIGGERCOUNTER;

void BulletMain(void){  // Later add input asking for max number of bullets
    TriggerCount --;
    Trigger = NO_FIRE;
    if(TriggerCount <= 0){
        TriggerCount = TRIGGERCOUNTER;
        Trigger = FIRE;
    }
    createBullet(Trigger);  
    if(bulletnum == 0){
        bulletnum = 20000;
        for(uint32_t i = 0; i < BULLETNUM_INVADER; i++){
            checkBulletEnemy(&(PlayerBullets[i]));
            checkBulletEdge(&(PlayerBullets[i]));
            moveBullet(&(PlayerBullets[i]));

        }
    }
    bulletnum--;
}
        


        
    
        
        



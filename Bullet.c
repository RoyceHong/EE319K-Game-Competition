// Bullet.c


#include <stdint.h>
#include "Bullet.h"
#include "ST7735.h"
#include "DisplayMap.h"
#include "enemy.h"
#include "tm4c123gh6pm.h"
#include "MainMenu.h"
#include "Sound.h"
#include "Random.h"
#include "BulletHell.h"


// Player structure
extern sprite_t Player1;
// Enemy array
extern sprite_t Enemies[ENEMY_ROW][ENEMY_COLUMN];
// Bunker array
extern sprite_t Bunkers[OBSTACLE_SIZE];
// variable keeping track of button press
extern uint8_t buttonStatus;
// enum determining whether game has been beaten or not 
extern progress_t gameProgress;
// variable indicating whether player is playing space invaders
extern uint8_t spaceInvadersRestriction;

// bullet array definitions
bullet_t PlayerBullets[PLAYER_BULLETNUM];
bullet_t EnemyBullets[BULLETNUM_INVADER];
fireBullet_t Trigger;

// variable keeping track of number of bullets for player 
uint32_t BulletCount = 0;
// variable keeping track of number of bullets for enemy 
uint32_t EnemyBulletCount = 0;



// initializes all bullets in bullet array to black  
void Bullet_Init(void){
    for(uint32_t i = 0; i < PLAYER_BULLETNUM; i++){
        PlayerBullets[i].color = BLACK;
    }
    for(uint32_t j = 0; j < BULLETNUM_INVADER; j++){
        EnemyBullets[j].color = BLACK;
    }
}


// chooses a random enemy in the enemy array to attack 
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


// creates bullets for the player 
uint8_t createBullet(fireBullet_t Condition, uint16_t BulletNum){
    if(Condition == FIRE){
        uint32_t i = 0;
        while(PlayerBullets[BulletCount].color != BLACK){
            BulletCount ++;
            BulletCount = BulletCount % BulletNum;
            if(i >= BulletNum){
                    return 0;
            }
            i++; 
        }

        PlayerBullets[BulletCount].h = 2;
        PlayerBullets[BulletCount].w = 2;
        PlayerBullets[BulletCount].x = Player1.x + (Player1.w/2) -1;
        PlayerBullets[BulletCount].y = Player1.y - (Player1.h) - 1;
        PlayerBullets[BulletCount].xvel = 0;
        PlayerBullets[BulletCount].yvel = -400;
        PlayerBullets[BulletCount].xvelSum = 0;
        PlayerBullets[BulletCount].yvelSum = 0;
        PlayerBullets[BulletCount].color = 0xFFFF;
        if(spaceInvadersRestriction == 1){
            SelectSound(SHOOT_SOUND);
        }
    }
    return 1;
}


// creates bullets for the enemy 
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
            EnemyBullets[EnemyBulletCount].yvel = 100;
            EnemyBullets[EnemyBulletCount].xvelSum = 0;
            EnemyBullets[EnemyBulletCount].yvelSum = 0;
            EnemyBullets[EnemyBulletCount].color = 0x07E0; 

        }
        return 1;
}


// check if player has been hit by a bullet 
void checkBulletPlayer(bullet_t* Shot){
    contact_t BulletStatus;
    if(Player1.life == ALIVE && (*Shot).color != BLACK){
        // hibox is full player sprite
        if(spaceInvadersRestriction == 1){
            BulletStatus = hitBoxCheck(Shot , &Player1);
        }
        // hitbox is 4x4 square at the center of player sprite
        else{
            BulletStatus = hitBoxCheckHell(Shot, &Player1);
        }
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



// check if enemy has been hit by a bullet
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


// check if bullets have reached the edge of the screen
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


// check if bullets have hit the bunker (for Space Invaders portion of the game)
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
            

// universal collision detection function
contact_t hitBoxCheck(bullet_t* bullet, sprite_t* object){
    if( ((bullet -> x >= object -> x) && (bullet -> x <= (object -> x + object -> w - 1)) )
        && ((bullet -> y <= object -> y) && (bullet -> y >= (object -> y - object -> h - 2)) )){ 
           return CONTACT;
    }
    else{
           return NO_CONTACT;
    }
 }

 
// universal edge detection function
contact_t edgeCheck(bullet_t* bullet){ 
     if( (bullet -> x <= 1) || (bullet -> x >= (DISPLAY_WIDTH - 1)) 
        || (bullet -> y <= 1) || (bullet -> y >= (DISPLAY_HEIGHT - 1)) ){
            
        return CONTACT;
     }
     else{
        return NO_CONTACT;
     }
}


// Moves bullets
void moveBullet(bullet_t *Shot){
    if((*Shot).color != BLACK){
        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, BLACK);
        // Update Bullet Coordinates
        (*Shot).x = (*Shot).x + (*Shot).xvelSum/100;
        (*Shot).y = (*Shot).y + (*Shot).yvelSum/100;
        (*Shot).xvelSum =  ((*Shot).xvelSum + (*Shot).xvel) % (100 + abs((*Shot).xvel));
        (*Shot).yvelSum =  ((*Shot).yvelSum + (*Shot).yvel) % (100 + abs((*Shot).yvel));
        
        // New Bullet
        ST7735_FillRect( (*Shot).x, (*Shot).y, (*Shot).w, (*Shot).h, (*Shot).color);
    }
}

int16_t abs(int16_t num){
    if(num < 0){
        num = 0 - num; 
    }
    return num;
}


// Determines how often enemy bullets are shot 
uint32_t TriggerCount = 0;
// Determines how often player is allowed to shoot
uint32_t TriggerCountPlayer = 0;
fireBullet_t TriggerEnemy;


// Main function in charge of manipulating enemy bullets (Space Invaders)
void EnemyBullet(void){
    // bulletSpeed determines how fast bullet travels on screen 
    static uint32_t bulletSpeed = ENEMYBULLETSPEED;  
    if(TriggerCount > 1){
        TriggerCount --;
    }
    TriggerEnemy = NO_FIRE;
    if(TriggerCount <= 1){
        TriggerCount = TRIGGERCOUNTERENEMY;
        TriggerEnemy = FIRE;
    }
    createEnemyBullet(TriggerEnemy, enemyAttack());   
    if(bulletSpeed == 0){
        bulletSpeed = ENEMYBULLETSPEED;
        for(uint32_t i = 0; i < BULLETNUM_INVADER; i++){
            // manipulate enemy bullets 
            checkBulletPlayer(&(EnemyBullets[i]));
            checkBulletObstacle(&(EnemyBullets[i]));
            checkBulletEdge(&(EnemyBullets[i]));
            moveBullet(&(EnemyBullets[i]));
        }
    }
    bulletSpeed--;
}


// main function in charge of manipulating the player bullets
void PlayerBullet(void){
    static uint32_t bulletSpeed = BULLETSPEEDP; 
    if(TriggerCountPlayer > 0){
        TriggerCountPlayer --;
    }
    Trigger = NO_FIRE;
    
    if(TriggerCountPlayer <= 1){
        Trigger = checkButton();
        if(Trigger == FIRE){
            TriggerCountPlayer = TRIGGERCOUNTERPLAYER;
        }
    }
    createBullet(Trigger, BULLETNUM_INVADER); 
    
    if(bulletSpeed == 0){
        bulletSpeed = BULLETSPEEDP;
        for(uint32_t i = 0; i < BULLETNUM_INVADER; i++){
            // manipulate player bullets
            checkBulletEnemy(&(PlayerBullets[i]));
            checkBulletObstacle(&(PlayerBullets[i]));
            checkBulletEdge(&(PlayerBullets[i]));
            moveBullet(&(PlayerBullets[i]));
        }
    }
    bulletSpeed--;
}


// checks if the button has been pressed 
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
        
        
    
    
        


        
    
        
        



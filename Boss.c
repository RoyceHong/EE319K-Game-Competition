// Boss.c
// Contains all the information on bosses encountered during the bullet hell portion of the game 

#include <stdint.h>
#include "Boss.h"
#include "ST7735.h"
#include "DisplayMap.h"
#include "Movement.h"

uint32_t Random(void);

extern const uint16_t StackOverflow[];
uint8_t bossNum = 0;
uint32_t bosstime = BOSSMOVE_TIMER;

// color definitions
uint16_t randColor = 0;
uint16_t red, lblue, dblue, pink, green, yellow, orange;


// velocity maps for each of the attack patterns 
velocity_t ConeVertVel[] = {
    {0, 100}, {-26, 96}, {-50, 87}, {-71, 71}, {-87, 50}, {-96, 26}, 
    {-87, 50}, {-71, 71}, {-50, 87}, {-26, 96}, {0, 100},
    {26, 96}, {50, 87}, {71, 71}, {87, 50}, {96, 26},
    {87, 50}, {71, 71}, {50,  87},  {26, 96}
};
    
velocity_t CircleBlastVel[] = {
    {0, 100}, {-20, 80}, {-40, 60}, {-60, 40}, {-80, 20}, {-100, 0},
    {-80, -20}, {-60, -40}, {-40, -60}, {-20, -80}, {0, -100},
    {20, -80}, {40, -60}, {60, -40}, {80, -20}, {100, 0},
    {80, 20}, {60, 40}, {40, 60}, {20, 80}
};

velocity_t BeamVel[] = {{0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}};


// attack patterns for bosses
atkpattern_t Boss1[] = {
    {1, ConeVertVel,  20, 0,7000, 8000},       // Vertical Cone Attack
    {20, CircleBlastVel, 20, 0, 13000, 5000},   // Circle Blast
    {1, BeamVel, 8, 0, 5000, 5000}             // Straight Beam
};

//atkpattern_t Boss2[];

//atkpattern_t Boss3[];



// array containing all the bosses 
boss_t Bosses[] ={
 {54, 60, StackOverflow, 12, 18, 1, 0, ALIVE, 100}
};

 
// Draws the boss on the screen 
void Boss_Init(uint8_t stage){
    ST7735_DrawBitmap(Bosses[stage].x, Bosses[stage].y, Bosses[stage].image, Bosses[stage].w, Bosses[stage].h);
}
    

atkpattern_t ChooseRandAttack(void){
    uint32_t random = (Random() % BOSS1_ATTACKNUM);
    return Boss1[random];
}


void Color_Init(void){
    red = ST7735_Color565(240, 114, 114);
    lblue = ST7735_Color565(87, 255, 255);
    dblue = ST7735_Color565(7, 57, 255);
    pink = ST7735_Color565(197, 46, 213);
    green = ST7735_Color565(75, 255, 124);
    yellow = ST7735_Color565(255, 255, 75);
    orange = ST7735_Color565(255, 130, 75); 
    
    Boss1[0].color = red;
    Boss1[1].color = lblue;
    Boss1[2].color = yellow;
}


void Move_Boss(void){ 
    // moves enemies in the horizontal direction
    if(bosstime == 0){
        // reset enemy timer 
        bosstime = BOSSMOVE_TIMER;
        // Check enemy positions and set velocity values   
        if(Bosses[bossNum].x <= 0){
            Bosses[bossNum].xvel = 1;
        }
        if(Bosses[bossNum].x + Bosses[bossNum].w >= DISPLAY_WIDTH){
            Bosses[bossNum].xvel = -1;
        }
        MoveBoss(&Bosses[bossNum]);
    }
    else{
        bosstime--;
    }
}


void MoveBoss(boss_t* object){
    if( ((object -> x + object -> xvel) >= 0) && ((object -> x + object -> xvel + object -> w) <= DISPLAY_WIDTH) ){
        (object -> x) = (object -> x) + (object -> xvel);
    }
    if(object -> life == ALIVE){
        ST7735_DrawBitmap(object -> x, object -> y, object -> image, object -> w, object -> h);
    }
}


// Boss.c
// Contains all the information on bosses encountered during the bullet hell portion of the game 

#include <stdint.h>
#include "Boss.h"
#include "ST7735.h"


uint32_t Random(void);

extern const uint16_t StackOverflow[];
uint8_t bossNum = 0;

// color definitions
uint16_t randColor = 0;
uint16_t red, lblue, dblue, pink, green, yellow, orange;

// velocity maps for each of the attack patterns 
velocity_t ConeVertVel[] = {{0, 2}, {-1, 2}, {-1, 1}, {-1, 2}, {0, 2}, {1, 2}, {1, 1}, {1, 2}};
velocity_t CircleBlastVel[] = {{0, 2}, {-1, 2}, {-1, 1}, {-2, 1}, {-2, 0}, {-2, -1}, {-1, -1}, {-1, -2}, {0, -2}, {1, -2}, {1, -1}, {2, -1}, {2, 0}, {2, 1}, {1, 1}, {1, 2}};
velocity_t BeamVel[] = {{0, 1}};


// attack patterns for bosses
atkpattern_t Boss1[] = {
    {1, ConeVertVel,  8, 7000, 90000},       // Vertical Cone Attack
    {16, CircleBlastVel, 16, 13000, 170000},   // Circle Blast
    {1, BeamVel, 1, 5000, 50000}             // Straight Beam
};

//atkpattern_t Boss2[];

//atkpattern_t Boss3[];



// array containing all the bosses 
boss_t Bosses[] ={
 {54, 30, StackOverflow, 12, 18, 0, 0, ALIVE, 375}
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
    pink = ST7735_Color565(87, 255, 255);
    green = ST7735_Color565(87, 255, 255);
    yellow = ST7735_Color565(87, 255, 255);
    orange = ST7735_Color565(87, 255, 255); 
}


/*
uint16_t ChooseRandColor(void){
    while(randColor == 0){
        randColor = ST7735_Color565((Random() % 255), (Random() % 255), (Random() % 255));
    }
    return randColor;
}
*/



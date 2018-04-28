// Boss.c
// Contains all the information on bosses encountered during the bullet hell portion of the game 

#include <stdint.h>
#include "Boss.h"
#include "ST7735.h"


uint32_t Random(void);

extern const uint16_t StackOverflow[];
uint8_t bossNum = 0;

int16_t ConeVertX[] = {0, -1, -1, -1, -1, 0, 1, 1, 1, 1};
int16_t ConeVertY[] = {2, 2, 1, 1, 2, 2, 2, 1, 1, 2};
int16_t BeamX[] = {1};
int16_t BeamY[] = {1};

atkpattern_t ConeVertical = {1, ConeVertX, ConeVertY, 9};

atkpattern_t Beam = {1, BeamX, BeamY, 1};


// array containing all the bosses 
boss_t Bosses[] ={
 {54, 30, StackOverflow, 12, 18, 0, 0, ALIVE, 375}
};

 
// Draws the boss on the screen 
void Boss_Init(uint8_t stage){
    ST7735_DrawBitmap(Bosses[stage].x, Bosses[stage].y, Bosses[stage].image, Bosses[stage].w, Bosses[stage].h);
}
    








void Boss_Move(){
    
}



// Boss.c
// Contains all the information on bosses encountered during the bullet hell portion of the game 

#include <stdint.h>
#include "Boss.h"
#include "ST7735.h"


extern const uint16_t StackOverflow[];
uint8_t bossNum = 0;

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



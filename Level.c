// Level.c 

#include <stdint.h>
#include "level.h"
#include "ST7735.h"
#include "Player.h"
#include "enemy.h"

extern const uint16_t Bunker0[];

// Bunker initial definition
sprite_t Bunkers[OBSTACLE_SIZE] = { 
    {25, 140, Bunker0, 18, 5, 0, 0, ALIVE}, 
    {90, 140, Bunker0, 18, 5, 0, 0, ALIVE}
};

sprite_t Bunker1 = {25, 140, Bunker0, 18, 5, 0, 0, ALIVE};
sprite_t Bunker2 = {90, 140, Bunker0, 18, 5, 0, 0, ALIVE}; 


// Initializes the first space invaders level
void Level_Init(){
    
    // Make screen blank 
    ST7735_FillScreen(0x0000);
    
    // Draw bunker on screen
    ST7735_DrawBitmap(Bunker1.x, Bunker1.y,  Bunker1.image, Bunker1.w, Bunker1.h);
    ST7735_DrawBitmap(Bunker2.x, Bunker2.y,  Bunker2.image, Bunker2.w, Bunker2.h);
    
    Player_Init();
    Enemy_Init();
}





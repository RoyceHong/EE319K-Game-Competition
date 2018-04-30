// Boss.c
// Contains all the information on bosses encountered during the bullet hell portion of the game 

#include <stdint.h>
#include "Boss.h"
#include "ST7735.h"
#include "DisplayMap.h"
#include "Movement.h"
#include "Random.h"

// Sprites for the boss 
extern const uint16_t StackOverflow[];

// velocity maps for each of the attack patterns 
const velocity_t ConeVertVel[] = {
    {0, 100}, {-26, 96}, {-50, 87}, {-71, 71}, {-87, 50}, {-96, 26}, 
    {-87, 50}, {-71, 71}, {-50, 87}, {-26, 96}, {0, 100},
    {26, 96}, {50, 87}, {71, 71}, {87, 50}, {96, 26},
    {87, 50}, {71, 71}, {50,  87},  {26, 96}
};
    
const velocity_t CircleBlastVel[] = {
    {0, 100}, {-20, 80}, {-40, 60}, {-60, 40}, {-80, 20}, {-100, 0},
    {-80, -20}, {-60, -40}, {-40, -60}, {-20, -80}, {0, -100},
    {20, -80}, {40, -60}, {60, -40}, {80, -20}, {100, 0},
    {80, 20}, {60, 40}, {40, 60}, {20, 80}
};

const velocity_t BeamVel[] = {{0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}, {0, 50}};

/*
velocity_t SpiralVel[] = {
    {0, 100}, {-20, 80}, {-40, 60}, {-60, 40}, {-80, 20}, {-100, 0}, {-80, -20}, {-60, -40}, {-40, -60}, {-20, -80}, {0, -100}, {20, -80}, {40, -60}, {60, -40}, {80, -20}, {100, 0}, {80, 20}, {60, 40}, {40, 60}, {20, 80},
    {-9, 99}, {-29, 79}, {-49, 59}, {-69, 39}, {-89, 19}, {-91, -1}, {-71, -21}, {-51, -41}, {-31, -61}, {-11, -81}, {9, -99}, {29, -79}, {49, -59}, {69, -39}, {89, -19}, {91, 9}, {71, 21}, {51, 41}, {31, 61}, {11, 81},
    {-17, 98}, {-37, 78}, {-57, 58}, {-77, 38}, {-97, 18}, {-83, -2}, {-63, -22}, {-43, -42}, {-23, -62}, {-3, -82}, {17, -98}, {37, -78}, {57, -58}, {77, -38}, {97, -18}, {83, 2}, {63, 22}, {43, 42}, {23, 62}, {3, 82},
    {-26, 97}, {-46, 77}, {-66, 57}, {-86, 37}, {-94, 17}, {-74, -3}, {-54, -23}, {-34, -43}, {-14, -63}, {6, -83}, {26, -97}, {46, -77}, {66, -57}, {86, -37}, {94, -17}, {74, 3}, {54, 23}, {34, 43}, {14, 63}, {-6, 83},
    {-34, 94}, {-54, 74}, {-74, 54}, {-94, 34}, {-86, 14}, {-66, -6}, {-46, -26}, {-26, -46}, {-6, -66}, {14, -86}, {34, -94}, {54, -74}, {74, -54}, {94, -34}, {86, -14}, {66, 6}, {46, 26}, {26, 46}, {6, 66}, {-14, 86},
    {-42, 91}, {-62, 71}, {-82, 51}, {-98, 31}, {-78, 11}, {-58, -9}, {-38, -29}, {-18, -49}, {2, -69}, {22, -89}, {42, -91}, {62, -71}, {82, -51}, {98, -31}, {78, -11}, {58, 9}, {38, 29}, {18, 49}, {-2, 69}, {-22, 89},
    {-50, 87}, {-70, 67}, {-90, 47}, {-90, 27}, {-70, 7}, {-50, -13}, {-30, -33}, {-10, -53}, {10, -73}, {30, -93}, {50, -87}, {70, -67}, {90, -47}, {90, -27}, {70, -7}, {50, 13}, {30, 33}, {10, 53}, {-10, 73}, {-30, 93},
    {-57, 82}, {-77, 62}, {-97, 42}, {-83, 22}, {-63, 2}, {-43, -18}, {-23, -38}, {-3, -58}, {17, -78}, {37, -98}, {57, -82}, {77, -62}, {97, -42}, {83, -22}, {63, -2}, {43, 18}, {23, 38}, {3, 58}, {-17, 78}, {-37, 98},
    {-64, 77}, {-84, 57}, {-96, 37}, {-76, 17}, {-56, -3}, {-36, -23}, {-16, -43}, {4, -63}, {24, -83}, {44, -97}, {64, -77}, {84, -57}, {96, -37}, {76, -17}, {56, 3}, {36, 23}, {16, 43}, {-4, 63}, {-24, 83}, {-44, 97},
    {-71, 71}, {-91, 51}, {-89, 31}, {-69, 11}, {-49, -9}, {-29, -29}, {-9, -49}, {11, -69}, {31, -89}, {51, -91}, {71, -71}, {91, -51}, {89, -31}, {69, -11}, {49, 9}, {29, 29}, {9, 49}, {-11, 69}, {-31, 89}, {-51, 91}
};
*/

const velocity_t SpiralVel[] = {
    {0, 100},  {-40, 60},  {-80, 20},  {-80, -20},  {-40, -60},  {0, -100},  {40, -60},  {80, -20},  {80, 20},  {40, 60},
    {-9, 99},  {-49, 59},  {-89, 19},  {-71, -21}, {-31, -61},  {9, -99},  {49, -59},  {89, -19}, {71, 21},  {31, 61}, 
    {-17, 98}, {-57, 58}, {-97, 18}, {-63, -22}, {-23, -62}, {17, -98},{57, -58}, {97, -18}, {63, 22}, {23, 62},
    {-26, 97}, {-66, 57},  {-94, 17},  {-54, -23},  {-14, -63}, {26, -97},  {66, -57},  {94, -17},  {54, 23},  {14, 63},
    {-34, 94}, {-74, 54},  {-86, 14},  {-46, -26},  {-6, -66},  {34, -94}, {74, -54}, {86, -14},  {46, 26},  {6, 66}, 
    {-42, 91}, {-82, 51},  {-78, 11},  {-38, -29},  {2, -69}, {42, -91}, {82, -51},  {78, -11},  {38, 29}, {-2, 69}, 
    {-50, 87},  {-90, 47},  {-70, 7}, {-30, -33},  {10, -73},  {50, -87},  {90, -47},  {70, -7}, {30, 33},  {-10, 73}, 
    {-57, 82},  {-97, 42},  {-63, 2},  {-23, -38},  {17, -78},  {57, -82},  {97, -42}, {63, -2},  {23, 38},  {-17, 78}, 
    {-64, 77}, {-96, 37},  {-56, -3},  {-16, -43},  {24, -83}, {64, -77},{96, -37},  {56, 3}, {16, 43},  {-24, 83}, 
    {-71, 71}, {-89, 31}, {-49, -9}, {-9, -49},  {31, -89},  {71, -71},  {89, -31},  {49, 9}, {9, 49}, {-31, 89}
};


const velocity_t Spray[42];

const velocity_t Burst[42];


// ATTACK PATTERNS FOR BOSSES
// Boss 1 Attack Patterns
atkpattern_t Boss1[] = {
    {0, 1, ConeVertVel,  20, 0, 250, 5000},       // Vertical Cone Attack
    {1, 20, CircleBlastVel, 20, 0, 500, 7500},   // Circle Blast
    {2, 1, BeamVel, 8, 0, 400, 6000},             // Straight Beam
    {3, 10, SpiralVel, 100, 0, 500, 10000}       // Spiral         
};

//atkpattern_t Boss2[];

//atkpattern_t Boss3[];

// add an array consisting of all bosses attack patterns (atkpattern_t BossAttacks)
atkpattern_t* BossAttacks[] = {Boss1};

// function that generates a random number
//uint32_t Random(void);

// global variable defining which boss is being fought 
uint8_t bossNum = 0;
// timer for boss movement 
uint32_t bosstime = BOSSMOVE_TIMER;
// variables that will hold color definitions
uint16_t red, lblue, dblue, pink, green, yellow, orange;


// array containing all the bosses 
boss_t Bosses[] ={
 {54, 60, StackOverflow, 12, 18, 1, 0, ALIVE, 100},
 // Boss2
 // Boss3
};

 
// Draws the boss on the screen 
void Boss_Init(uint8_t bossNumber){
    ST7735_DrawBitmap(Bosses[bossNumber].x, Bosses[bossNumber].y, Bosses[bossNumber].image, Bosses[bossNumber].w, Bosses[bossNumber].h);
}


// chooses a random attack 
uint8_t ChooseRandAttack(void){
    uint8_t random = (Random() % BOSS1_ATTACKNUM);
    return random;
}


// Initializes colors
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
    Boss1[3].color = orange;
}


// Main function for moving the boss
void Move_Boss(void){ 
    // moves boss in the horizontal direction
    if(bosstime == 0){
        // reset boss timer
        bosstime = BOSSMOVE_TIMER;
        // Check boss positions and set velocity values   
        if(Bosses[bossNum].x <= 30){
            Bosses[bossNum].xvel = 1;
        }
        if(Bosses[bossNum].x + Bosses[bossNum].w >= 90){
            Bosses[bossNum].xvel = -1;
        }
        // Moves boss
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


#include <stdint.h>
#include "ST7735.h"
#include "CutScene.h"
#include "Player.h"
#include "MainMenu.h"
#include "Movement.h"
#include "Button.h"


extern const uint16_t SayakaHappy[];
extern const uint16_t SayakaBlush[];
extern const uint16_t SayakaNeutral[];
extern const uint16_t SayakaInLove[];
extern const uint16_t SayakaScared[];
extern const uint16_t Arrow[];
extern progress_t gameProgress;
extern movestate_t CurrentMove;

// Sprite must be < 6 pix wide
sprite_t PlayerSelect = {1,  146, Arrow,  4, 7, 0, 0, ALIVE};

image_t Sayaka_Happy = {SayakaHappy, 108, 120};
image_t Sayaka_Blush = {SayakaBlush, 127, 120};
image_t Sayaka_Neutral = {SayakaNeutral, 121, 120};
image_t Sayaka_InLove = {SayakaInLove, 128, 101};
image_t Sayaka_Scared = {SayakaScared, 128, 116};

const scene_t Sayaka_Stage1[] = {
	{{SayakaNeutral, 121, 120}, "Not Bad.", 0, 0, 0, 500, {2, 2}}, 	// Reaction1 (Beat Level)
	{{SayakaScared, 128, 116}, "How Unfortunate...", 0, 0, 0, 0, {1, 1}},	// Reaction2 (Lost Level)
	
	{{SayakaNeutral, 121, 120}, "What? Suprised? ", 0, 0, 0, 0, {1, 1}},
    {{SayakaNeutral, 121, 120}, "Truth is, game is", "actually a simulator.", 0, 0, 0, {1, 1}},
    {{SayakaHappy, 108, 120}, "I'm here to evaluate", "your value as garbage", 0, 0, 0, {1, 1}},
    {{SayakaHappy, 108, 120}, "to see if you have", "any hope of escaping", 0, 0, 0, {1, 1}},

	{{SayakaHappy, 108, 120}, "this pitiful single", "life of yours.", "Why?", "What the...", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{SayakaInLove, 128, 101}, "It amuses me.", 0, 0, 0, 50,	{2, 2}},	// Reaction1 (Right)
	{{SayakaBlush, 127, 120}, "That's no good...", 0, 0, 0, 0, {1, 1}},	    // Reaction2 (Wrong)

	{{SayakaScared, 128, 116}, "What you say affects", "your evaluation.", 0, 0, 0, {1, 1}},
    
	{{SayakaInLove, 128, 101}, "So be careful what", "you say.", "Are you kidding!?", "Gotchu", 0, {WRONGCHOICE, RIGHTCHOICE}},
	{{SayakaHappy, 108, 120}, "Good.", 0, 0, 0, 50, {2, 2}},	                        // Reaction1 (Right)
	{{SayakaScared, 128, 116}, "You're hopeless", 0, 0, 0, 0, {1, 1}},				// Reaction2 (Wrong)

    {{SayakaNeutral, 121, 120}, "Also keep in mind", "that your preformance", 0, 0, 0, {1, 1}},
    {{SayakaNeutral, 121, 120}, "on other portions", "of the simulation", 0, 0, 0, {1, 1}},
    {{SayakaNeutral, 121, 120}, "are part of your", "final verdict.", 0, 0, 0, {1, 1}},
    
    {{SayakaHappy, 108, 120}, "With introductions", "out of the way,", 0, 0, 0, {1, 1}},
    {{SayakaHappy, 108, 120}, "how about we move on", "to the next section.", "Yes", "No", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{SayakaNeutral, 121, 120}, "Let's begin", 0, 0, 0, 50, {0, 0}},          // Right
	{{SayakaScared, 128, 116}, "... ", 0, 0, 0, 0, {0, 0,}}                   // Wrong
};

const scene_t Sayaka_Stage2[] = {
	{{SayakaNeutral, 121, 120}, "Wow.", 0, 0, 0, 100, {2, 2}},	// Reaction 1 (Beat Level)
	{{SayakaBlush, 127, 120}, "Pathetic...", 0, 0, 0, 0, {1, 1}}, 	// Reaction 2 (Lost Level)
	
	{{SayakaNeutral, 121, 120}, "How are you feeling?", 0, "I'm gucci", "I'm dying",  0, {WRONGCHOICE, RIGHTCHOICE}},
	{{SayakaHappy, 108, 120}, "I think that's", "everyday for you.", 0, 0, 50, {2, 2}},		// Reaction1 (Right)
	{{SayakaNeutral, 121, 120}, "Oh, are you now?", 0, 0, 0, 0, {1, 1}}, 		// Reaction2 (Wrong)

	{{SayakaBlush, 127, 120}, "I'm not sure how", "to say this...", 0, 0, 0, {1, 1}},
	{{SayakaBlush, 127, 120}, "But will you go on ", "a date with me?", "Of Course!", "Give me a moment", 0, {WRONGCHOICE, RIGHTCHOICE}},
	{{SayakaNeutral, 121, 120}, "Good answer.", 0, 0, 0, 100, {2, 2}},		        // Reaction1 (Right)
	{{SayakaScared, 128, 116}, "How desperate...", 0, 0, 0, -100, {1, 1}}, 		    // Reaction2 (Wrong)
    
    {{SayakaNeutral, 121, 120}, "Remember, if a girl", "asks you out,", 0, 0, 0, {1, 1}}, 
    {{SayakaNeutral, 121, 120}, "its definitely a ", "prank.", 0, 0, 0, {1, 1}},
    
    {{SayakaNeutral, 121, 120}, "You are an engineer.", 0, 0, 0, 0, {1, 1}},
    
    {{SayakaNeutral, 121, 120}, "Any hope is just", "an illusion.", 0, 0, 0, {1, 1}},

	{{SayakaNeutral, 121, 120}, "Expecting some girl", "to come up and say", 0, 0, 0, {1, 1}},   
    {{SayakaInLove, 128, 101}, "'I always loved you'", 0, 0, 0, 0, {1, 1}},
    {{SayakaNeutral, 121, 120}, "is trash you only", "see in fiction.", "I am trash", "Sounds personal", 0, {RIGHTCHOICE, WRONGCHOICE}},
    {{SayakaHappy, 108, 120}, "I'm glad you", "understand.", 0, 0, 50, {2, 2}},		// Reaction1 (Right)
    {{SayakaNeutral, 121, 120}, "Quiet.", 0, 0, 0, -50, {1, 1}},		// Reaction2 (Wrong)
    
    {{SayakaBlush, 127, 120}, "That being said...", 0, 0, 0, 0, {1, 1}},
    {{SayakaNeutral, 121, 120}, "Let's continue,", 0, 0, 0, 0, {0, 0}}
};



		



// ST7735_DrawBitmap(0, 120, Sayaka_Stage1[Current_Scene].image, Sayaka_Stage1[Current_Scene].w, Sayaka_Stage1[Current_Scene].h);

// uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){


void displayScene(scene_t* StageScene){
	// drawBitMAP StageScene->Image
    ST7735_FillRect(0, 0, 128, 160, 0x0000);
    ST7735_DrawBitmap(0, 118, (StageScene -> SayakaChan).image, (StageScene -> SayakaChan).w, (StageScene -> SayakaChan).h);
	//Draw Line
    ST7735_FillRect(0, 119, 128, 1, 0xFFFF);
	//DrawString Sayaka Dialogue
    uint16_t Line = 12;
    uint16_t Column = 0;
    uint16_t CharPrinted = ST7735_DrawString(Column, Line, StageScene -> SayakaDialogue, 0xFFFF);
    Line += 1;
    if(StageScene -> SayakaDialogue2 != 0){
        ST7735_DrawString(Column, Line, StageScene -> SayakaDialogue2, 0xFFFF);
    }
    while(Button_In() == 0){}
    while(Button_In() != 0){}
	//DrawString Character Dialogue 1
    Line += 1;
    Column += 1;
    if(StageScene -> PlayerOption1 != 0){
        CharPrinted = ST7735_DrawString(Column, Line, StageScene -> PlayerOption1, 0xFFFF);
    }
	//DrawString Charcter Dialogue 2
    Line += 1;
    if(StageScene -> PlayerOption1 != 0){
        CharPrinted = ST7735_DrawString(Column, Line, StageScene -> PlayerOption2, 0xFFFF);
    }
}


uint8_t Select(scene_t* StageScene){
	uint8_t SelectedMove = OPTIONONE;
    if(StageScene -> NextScene[OPTIONONE] != StageScene -> NextScene[OPTIONTWO]){
        PlayerSelect.y = 146;
        ST7735_DrawBitmap(PlayerSelect.x, PlayerSelect.y, PlayerSelect.image, PlayerSelect.w,  PlayerSelect.h);
        while(Button_In() == 0){
            
            if(CurrentMove == UP){
                ST7735_FillRect(PlayerSelect.x , PlayerSelect.y - PlayerSelect.h, PlayerSelect.w, PlayerSelect.h, 0x0000);
                PlayerSelect.y = 146;
                ST7735_DrawBitmap(PlayerSelect.x, PlayerSelect.y, PlayerSelect.image, PlayerSelect.w,  PlayerSelect.h);
                SelectedMove = OPTIONONE;
            }
            else if(CurrentMove == DOWN){
                ST7735_FillRect(PlayerSelect.x , PlayerSelect.y - PlayerSelect.h, PlayerSelect.w, PlayerSelect.h, 0x0000);
                PlayerSelect.y = 156;
                ST7735_DrawBitmap(PlayerSelect.x, PlayerSelect.y, PlayerSelect.image, PlayerSelect.w,  PlayerSelect.h);
                SelectedMove = OPTIONTWO;
            }
        }
        while(Button_In() != 0){}
        
    }
    return StageScene -> NextScene[SelectedMove]; 
     

}

uint8_t Current_Scene;

void SceneMain(scene_t* SayakaStage){
	if(gameProgress == SUCCESS){
		Current_Scene = 0;
	}
	else if(gameProgress == FAIL){
		Current_Scene = 1;
	}

    while(1){
        displayScene(&SayakaStage[Current_Scene]);
        uint8_t changeScene = Select(&SayakaStage[Current_Scene]);
        Current_Scene = Current_Scene + changeScene ;
        if(changeScene == 0){
            break;
        }
    }			
}		
	






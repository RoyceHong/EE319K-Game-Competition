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
extern const uint16_t PlayerRightFrame_1[];
extern progress_t gameProgress;
extern movestate_t CurrentMove;

sprite_t PlayerSelect = {1,  140, PlayerRightFrame_1,  16, 11, 0, 0, ALIVE};

scene_t Sayaka_Stage1[] = {
	{{SayakaHappy, 108, 120}, "Nice Work!", 0, 0, 500, {2, 2}}, 	// Reaction1 (Beat Level)
	{{SayakaScared, 108, 120}, "How Unfortunate...", 0, 0, 0, {1, 1}},	// Reaction2 (Lost Level)
	
	{{SayakaNeutral, 121, 120}, "What's wrong? You seemed suprised. ", 0, 0, 0, {1, 1}},

	{{SayakaHappy, 108, 120}, "Maybe you still can't believe I asked you out", "I always thought you were out of my league.", "No, I'm a little shocked at something else.", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{SayakaInLove, 128, 101}, "Fufu, your always honest.", 0, 0, 500,	{2, 2}},	// Reaction1 (Right)
	{{SayakaScared, 108, 120}, "I wonder what that could be...", 0, 0, 50, {1, 2}},	// Reaction2 (Wrong)

	{{SayakaBlush, 127, 120}, "Whatever the case, I can't help but feel you're a little tense", 0, 0, 0, {1, 1}},
	{{SayakaNeutral, 121, 120}, "Are you feeling alright?", "There have been worse days.", "Yeah, I'm fine.", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{SayakaHappy, 108, 120}, "Your definitely not wrong about that.", 0, 0, 500, {2, 2}},	// Reaction1 (Right)
	{{SayakaHappy, 108, 120}, "That's good.", 0, 0, 200, {1, 1}},				// Reaction2 (Wrong)

	{{SayakaBlush, 127, 120}, "You must feel like things are a bit slow.", 0, 0, 0, {1, 1}},
	{{SayakaInLove, 128, 101}, "How about we kick things up a notch?", 0, 0, 0, {0, 0,}}
};

const scene_t Sayaka_Stage2[] = {
	{{SayakaHappy, 108, 120}, "Were you suprised?", 0, 0, 500, {2, 2}},	// Reaction 1 (Beat Level)
	{{SayakaScared, 108, 120}, "I guess I was being too harsh...", 0, 0, 0, {1, 1}}, 	// Reaction 2 (Lost Level)
	
	{{SayakaBlush, 127, 120}, "Was it too much for you?", "N-Not really.", "Yeah, kinda...",  0, {WRONGCHOICE, RIGHTCHOICE}},
	{{SayakaBlush, 127, 120}, "...", 0, 0, 500, {2, 2}},		// Reaction1 (Right)
	{{SayakaBlush, 127, 120}, "...", 0, 0, 250, {1, 1}}, 		// Reaction2 (Wrong)

	{{SayakaScared, 108, 120}, "...", 0, 0, 0, {1, 1}},
	{{SayakaScared, 108, 120}, "I guess I'm not really a good person", 0, 0, 0, {1, 1}},
	{{SayakaScared, 108, 120}, "Maybe I'm just a burden to you", "Of course you're not!", "I don't really understand what you're saying.", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{SayakaHappy, 108, 120}, "You really know how to make me smile.", 0, 0, 500, {2, 2}},		// Reaction1 (Right)
	{{SayakaBlush, 127, 120}, "Nevermind then...", 0, 0, -1000, {1, 1}}, 				// Reaction2 (Wrong)

	{{SayakaNeutral, 121, 120}, "If you don't mind, I'd like to try one more time.", 0, 0, 0, {0, 0}}
};



		



// ST7735_DrawBitmap(0, 120, Sayaka_Stage1[Current_Scene].image, Sayaka_Stage1[Current_Scene].w, Sayaka_Stage1[Current_Scene].h);

// uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){


void displayScene(scene_t* StageScene){
	// drawBitMAP StageScene->Image
    ST7735_FillRect(0, 0, 128, 160, 0x0000);
    ST7735_DrawBitmap(0, 120, (StageScene -> SayakaChan).image, (StageScene -> SayakaChan).w, (StageScene -> SayakaChan).h);
	//Draw Line
    ST7735_FillRect(0, 121, 128, 1, 0xFFFF);
	//DrawString Sayaka Dialogue
    uint16_t Line = 12;
    uint16_t Column = 0;
    uint16_t CharPrinted = ST7735_DrawString(Line, Column, StageScene -> SayakaDialogue, 0xFFFF);
    Line += 1;
    ST7735_DrawString(Line, Column, StageScene -> SayakaDialogue + CharPrinted, 0xFFFF);
    while(Button_In() == 0){}
	//DrawString Character Dialogue 1
    Line += 1;
    Column += 1;
    CharPrinted = ST7735_DrawString(Line, Column, StageScene -> PlayerOption1, 0xFFFF);
	//DrawString Charcter Dialogue 2
    Line += 1;
    Column += 1;
    CharPrinted = ST7735_DrawString(Line, Column, StageScene -> PlayerOption2, 0xFFFF);
}


uint8_t Select(scene_t* StageScene){
	uint8_t SelectedMove;
	while(Button_In() == 0){
		PlayerSelect.y = 140;
		if(CurrentMove == LEFT){
            ST7735_FillRect(PlayerSelect.x , PlayerSelect.y, PlayerSelect.w, PlayerSelect.h, 0x0000);
            PlayerSelect.y = 140;
            ST7735_DrawBitmap(PlayerSelect.x, PlayerSelect.y, PlayerSelect.image, PlayerSelect.w,  PlayerSelect.h);
			SelectedMove = OPTIONONE;
		}
		else if(CurrentMove == RIGHT){
            ST7735_FillRect(PlayerSelect.x , PlayerSelect.y, PlayerSelect.w, PlayerSelect.h, 0x0000);
            PlayerSelect.y = 150;
            ST7735_DrawBitmap(PlayerSelect.x, PlayerSelect.y, PlayerSelect.image, PlayerSelect.w,  PlayerSelect.h);
			SelectedMove = OPTIONTWO;
		}
	}
	return StageScene -> NextScene[SelectedMove];

}

<<<<<<< HEAD
=======

>>>>>>> 8af2a278471312f8476c23db0cb425719cb2c362
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
	






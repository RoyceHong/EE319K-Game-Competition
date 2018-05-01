#include <stdint.h>
#include "ST7735.h"
#include "CutScene.h"
#include "Player.h"
#include "MainMenu.h"
#include "Movement.h"
#include "Button.h"
#include "Sound.h"


extern const uint16_t Arrow[];
extern progress_t gameProgress;
extern movestate_t CurrentMove;
extern music_t DialogueSound;

extern const uint16_t Trumpalump[];
extern const uint16_t HappyTrump[];
extern const uint16_t TrumpF[];
extern const uint16_t SleepyTrump[];
extern const uint16_t TrumpAh[];
extern const uint16_t Obama[];

// Sprite must be < 6 pix wide
sprite_t PlayerSelect = {1,  146, Arrow,  4, 7, 0, 0, ALIVE};

image_t Trump_alump = {Trumpalump, 128, 113};
image_t Happy_Trump = {HappyTrump, 128, 92};
image_t Trump_F = {TrumpF, 128, 123};
image_t Sleepy_Trump = {SleepyTrump, 128, 81};
image_t Trump_Ah = {TrumpAh, 128, 90};
image_t Obama_Obama = {Obama, 128, 116};
<<<<<<< HEAD

=======
>>>>>>> e2286b3a6ec03dfca8b2d18b3839470795012441



const scene_t Sayaka_Stage1[] = {
	{{HappyTrump, 128, 92}, "Thank you for saving", "America from the", 0, 0, 500, {2, 2}}, 	// Reaction1 (Beat Level)
	{{Trumpalump, 128, 113}, "You failed to save", "America from the", 0, 0, 0, {1, 1}},	// Reaction2 (Lost Level)	
	{{HappyTrump, 128, 92}, "space invaders.", 0, 0, 0, 0, {1, 1}},
    
    {{Trumpalump, 128, 113}, "However, it seems", "like an even greater", 0, 0, 0, {1, 1}},
    {{Trumpalump, 128, 113}, "threat has appeared.", 0, 0, 0, 0, {1, 1}},
    
    {{TrumpAh, 128, 90}, "I have a lot of ", "money, so I can give", 0, 0, 0, {1, 1}},
	{{TrumpAh, 128, 90}, "you a small loan of", "one million dollars", 0, 0, 0, {1, 1}},
	{{TrumpAh, 128, 90}, "to upgrade your ", "spaceship.", 0, 0, 0,	{1, 1}},		    

	{{Trumpalump, 128, 113}, "Will you go out to ", "serve your country?", "Yes ", "No", 0, {RIGHTCHOICE, WRONGCHOICE}},
    {{SleepyTrump, 128, 81}, "I wish you good luck.", 0, 0, 0, 0, {0, 0}},	                        // Reaction1 (Right)
    {{TrumpF, 128, 123}, "...", 0, 0, 0, 0, {-2, -2}}				// Reaction2 (Wrong)  
};

const scene_t Sayaka_Stage2[] = {
	{{HappyTrump, 128, 92}, "Once again you have", "saved America from ", 0, 0, 100, {2, 2}},	// Reaction 1 (Beat Level)
	{{Trumpalump, 128, 113}, "You have brought", "America closer to", 0, 0, 0, {1, 1}}, 	// Reaction 2 (Lost Level)	
	{{HappyTrump, 128, 92}, "destruction.", 0, 0, 0,  0, {1, 1}},
    
	{{SleepyTrump, 128, 81}, "We're going to make ", "a great wall. ", 0, 0, 50, {1, 1}},		
    
	{{TrumpAh, 128, 90}, "Believe me, we're ", "going to take care", 0, 0, 0, {1, 1}}, 		// Reaction2 (Wrong)
	{{Trumpalump, 128, 113}, "of them. But before", "that I require", 0, 0, 0, {1, 1}},
    
	{{Trumpalump, 128, 113}, "you to continue your", "service.", "Anything for you", "No thanks", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{SleepyTrump, 128, 81}, "Godspeed brave", "soldier.", 0, 0, 100, {0, 0}},		        // Reaction1 (Right)
	{{TrumpF, 128, 123}, "...", 0, 0, 0, -100, {-2, -2}}		    // Reaction2 (Wrong) 
    
};

const scene_t Sayaka_Stage3[] = {
	{{Trumpalump, 128, 113}, "You have displayed", "the best courage in", 0, 0, 0, {2, 2}},	    
	{{Trumpalump, 128, 113}, "You have displayed", "the best courage in", 0, 0, 0, {1, 1}}, 		
	{{Trumpalump, 128, 113}, "your journey so far.", 0, 0, 0,  0, {1, 1}},
    
	{{SleepyTrump, 128, 81}, "But I have something", "to tell you.", 0, 0, 0, {1, 1}},		
    
	{{TrumpF, 128, 123}, "You thought you were", "following your hero,", 0, 0, 0, {1, 1}}, 		
	{{TrumpF, 128, 123}, "Trump.", 0, 0, 0, 0, {1, 1}},
    
	{{Obama, 128, 116}, "But it was I, ", "OBAMA!", "Nani!?", "Omae mo shindeiru", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{Obama, 128, 116}, "Uuuhhh...", "Yes we can.", 0, 0, 0, {0, 0}},		        // Reaction1 (Right)
	{{Obama, 128, 116}, "Uuuhhh...", "Yes we can.", 0, 0, 0, {0, 0}}		    // Reaction2 (Wrong) 
    
};


const scene_t Sayaka_Stage3[] = {
	{{Trumpalump, 128, 113}, "You have displayed", "the best courage in", 0, 0, 0, {2, 2}},	    
	{{Trumpalump, 128, 113}, "You have displayed", "the best courage in", 0, 0, 0, {1, 1}}, 		
	{{Trumpalump, 128, 113}, "your journey so far.", 0, 0, 0,  0, {1, 1}},
    
	{{SleepyTrump, 128, 81}, "But I have something", "to tell you.", 0, 0, 0, {1, 1}},		
    
	{{TrumpF, 128, 123}, "You thought you were", "following your hero,", 0, 0, 0, {1, 1}}, 		
	{{TrumpF, 128, 123}, "Trump.", 0, 0, 0, 0, {1, 1}},
    
	{{Obama, 128, 116}, "But it was I, ", "OBAMA!", "Nani!?", "Omae mo shindeiru", 0, {RIGHTCHOICE, WRONGCHOICE}},
	{{Obama, 128, 116}, "Uuuhhh...", "Yes we can.", 0, 0, 0, {0, 0}},		        // Reaction1 (Right)
	{{Obama, 128, 116}, "Uuuhhh...", "Yes we can.", 0, 0, 0, {0, 0}}		    // Reaction2 (Wrong) 
    
};



void displayScene(scene_t* StageScene){
	// drawBitMAP StageScene->Image
    ST7735_FillRect(0, 0, 128, 160, 0x0000);
    ST7735_DrawBitmap(0, 116, (StageScene -> SayakaChan).image, (StageScene -> SayakaChan).w, (StageScene -> SayakaChan).h);
	//Draw Line
    ST7735_FillRect(0, 117, 128, 1, 0xFFFF);
	//DrawString Sayaka Dialogue
    uint16_t Line = 12;
    uint16_t Column = 0;
    SelectSound(DIALOGUE_SOUND);
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


int8_t Select(scene_t* StageScene){
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

int8_t Current_Scene;

void SceneMain(scene_t* SayakaStage){
	if(gameProgress == SUCCESS){
		Current_Scene = 0;
	}
	else if(gameProgress == FAIL){
		Current_Scene = 1;
	}

    while(1){
        displayScene(&SayakaStage[Current_Scene]);
        int8_t changeScene = Select(&SayakaStage[Current_Scene]);
        Current_Scene = Current_Scene + changeScene ;
        if(changeScene == 0){
            break;
        }
    }			
}		
	






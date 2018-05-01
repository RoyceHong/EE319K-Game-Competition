// DisplayMap.c

#include "DisplayMap.h"
#include "tm4c123gh6pm.h"
#include "ST7735.h"

uint16_t Buffer1[BUFFER_HEIGHT][BUFFER_WIDTH];
extern uint16_t SleepFrame1[];
extern uint16_t SleepFrame2[];
extern int16_t BufferFlag;
sprite_t Sleep1 = {0, 0, SleepFrame1, 30, 13, 0, 0, ALIVE};
sprite_t Sleep2 = {0, 0, SleepFrame2, 30, 14, 0, 0, ALIVE};

void bufferClear(void){
     for(int16_t i = 0; i < DISPLAY_HEIGHT; i++){
        for(int16_t j = 0; j < DISPLAY_WIDTH; j++){
            Buffer1[i][j] = 0x0000;
        }
    }
}

void DrawImage_Buffer(sprite_t *object){
    uint32_t counter = 0;
	for(int a = 0; a < object -> h; a++){			// Index Y axis
		for(int b = 0; b < object -> w; b++){		// Index X axis
			Buffer1[(object ->y) +a][(object -> x)+b] = (object -> image[counter]);
			counter ++;
		}
	}
}
uint16_t FrameCheck;
void BufferMain(void){
    bufferClear();
    if(FrameCheck == 0){
        DrawImage_Buffer(&Sleep1);
        FrameCheck = 1;
    }
    else if(FrameCheck == 1){
        DrawImage_Buffer(&Sleep2);
        FrameCheck = 0;
    }
    while(BufferFlag != 0){}
    BufferFlag = 1;
}




#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <stdint.h>

#ifndef OPTIONONE
#define OPTIONONE 0
#endif

#ifndef OPTIONTWO
#define OPTIONTWO 1
#endif

#ifndef WRONGCHOICE
#define WRONGCHOICE 2
#endif 

#ifndef RIGHTCHOICE
#define RIGHTCHOICE 1
#endif

typedef struct image_t{
	const uint16_t *image;
	const int16_t w;
	const int16_t h;
} image_t;


typedef struct scene_t{
	struct image_t SayakaChan;
	char *SayakaDialogue;
	char *PlayerOption1;
	char *PlayerOption2;
	int32_t Points;
	uint8_t NextScene[2];
	
} scene_t;

extern const uint16_t SayakaHappy[];
extern const uint16_t SayakaBlush[];
extern const uint16_t SayakaNeutral[];
extern const uint16_t SayakaInLove[];
extern const uint16_t SayakaScared[];


const image_t Sayaka_Happy = {SayakaHappy, 108, 120};
const image_t Sayaka_Blush = {SayakaBlush, 127, 120};
const image_t Sayaka_Neutral = {SayakaNeutral, 121, 120};
const image_t Sayaka_InLove = {SayakaInLove, 128, 101};
const image_t Sayaka_Scared = {SayakaScared, 108, 120};


void displayScene(scene_t* StageScene);







#endif



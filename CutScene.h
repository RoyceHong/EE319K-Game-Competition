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
    char *SayakaDialogue2;
	char *PlayerOption1;
	char *PlayerOption2;
	int32_t Points;
	int8_t NextScene[2];
	
} scene_t;




void displayScene(scene_t* StageScene);
int8_t Select(scene_t* StageScene);
void SceneMain(scene_t* SayakaStage);






#endif



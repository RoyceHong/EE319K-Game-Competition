// Sound.h
// Runs on TM4C123 or LM4F120
// Prototypes for basic functions to play sounds from the
// original Space Invaders.
// Jonathan Valvano
// November 17, 2014

#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

#ifndef SHOOT_SOUND
#define SHOOT_SOUND 0
#endif

#ifndef MENU_SOUND_1
#define MENU_SOUND_1 1
#endif
    
#ifndef MENU_SOUND_2
#define MENU_SOUND_2 2
#endif

#ifndef DIALOGUE_SOUND
#define DIALOGUE_SOUND 3
#endif

#ifndef INVADER_KILL_SOUND
#define INVADER_KILL_SOUND 4
#endif


/*#ifndef INVADER_DIE_SOUND
#define INVADER_DIE_SOUND 5
#endif
*/

#ifndef BULLET_FIRE_SOUND
#define BULLET_FIRE_SOUND 6
#endif

#ifndef GAME_OVER_SOUND
#define GAME_OVER_SOUND 7
#endif

typedef enum {SOUNDON, SOUNDOFF} sound_t;

typedef struct music_t {
    const uint8_t* currentSound;
    uint32_t size;
}music_t;

void Sound_Init(void);

void Sound_Play(music_t* sound);

void SelectSound(uint8_t SoundInput);

#endif




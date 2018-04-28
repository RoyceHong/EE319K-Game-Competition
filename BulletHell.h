// BulletHell.h

#ifndef BULLETHELL_H
#define BULLETHELL_H

#include <stdint.h>
#include "bullet.h"
#include "Boss.h"

#ifndef BULLETNUM_HELL
#define BULLETNUM_HELL 99
#endif

#ifndef BULLETHELL_TRIGGER
#define BULLETHELL_TRIGGER 50000
#endif

// main function to manipulate player bullets during bullet hell game 
void PlayerBulletHell(void);


// check if player bullets have hit the boss
void checkBulletBoss(bullet_t* Shot);


contact_t BossBoxCheck(bullet_t* bullet, boss_t* object);






#endif


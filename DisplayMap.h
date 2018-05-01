// DisplayMap.h 

#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H

#include <stdint.h>
#include "player.h"

#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH 128
#endif

#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT 160
#endif

#ifndef BUFFER_WIDTH
#define BUFFER_WIDTH 30
#endif

#ifndef BUFFER_HEIGHT
#define BUFFER_HEIGHT 14
#endif

void bufferClear(void);
void DrawImage_Buffer(sprite_t *object);
void BufferMain(void);

#endif



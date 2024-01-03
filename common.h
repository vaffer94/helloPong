#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool processInput(void);

void timeUpdate(Uint32* lastFrameTime, float* deltaTime);

#endif // COMMON_H_
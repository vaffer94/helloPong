#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool printLogo(void);

bool processInput(void);

void timeUpdate(Uint32* lastFrameTime, float* deltaTime);

#endif // COMMON_H_
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "common.h"
#include "constants.h"
#include "initFuncs.h"
#include "updateFuncs.h"
#include "endFuncs.h"

SDL_Window*   window = NULL;
SDL_Renderer* renderer = NULL;
Ball ball;
bool served = false;
Player player1;
Player player2;

//****************************************************************************

int main(int argc, const char* argv[])
{
    printf("\n\nHello world!\n");
    printf("\U0001f984 - 👾\n\n");

    printIntVal(3);

    srand((unsigned int)time(NULL));
    atexit(shoutdown);

    // setup
    if (!initialize())
    {
        exit(1);
    }

    bool   quit     = false;
    Uint32 lastTick = SDL_GetTicks();

    while (!quit)
    {
        quit = processInput();

        Uint32 curTick = SDL_GetTicks();
        Uint32 diff    = curTick - lastTick;
        float  elapsed = diff / 1000.0f;

        // update and render
        update(elapsed);

        lastTick = curTick;
    }

    SDL_Quit();

    return 0;
}

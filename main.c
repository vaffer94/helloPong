#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "common.h"
#include "constants.h"
#include "endFuncs.h"
#include "initFuncs.h"
#include "updateFuncs.h"

SDL_Window*   window   = NULL;
SDL_Renderer* renderer = NULL;
bool          served   = false;
Ball          ball;
Player        player1;
Player        player2;

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

    // Uint32   lastTick      = SDL_GetTicks();
    bool     quit          = false;
    Uint32 lastFrameTime = 0;
    float deltaTime     = 0;

    while (!quit)
    {
        // catch user input
        quit = processInput();

        // logic to keep a fixed time step
        timeUpdate(&lastFrameTime, &deltaTime);
        // Uint32 curTick = SDL_GetTicks();
        // Uint32 diff    = curTick - lastTick;
        // float  elapsed = diff / 1000.0f;

        // update and render
        update(deltaTime);

        // lastTick = curTick;
    }

    SDL_Quit();

    return 0;
}

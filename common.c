#include "common.h"
#include "constants.h"

bool processInput(void)
{
    bool      isGameExit = false;
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isGameExit = true;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            isGameExit = true;
        break;

    default:
        break;
    }

    return isGameExit;
}

void timeUpdate(Uint32* lastFrameTime, float* deltaTime)
{
    // pixel per second, it is the amount elapsed since the last frame
    *deltaTime = (SDL_GetTicks() - *lastFrameTime) / 1000.0F;

    // waste some time / sleep until we reach the frame target time
    // while(!SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameRate + FRAME_TARGET_TIME));
    // [ERROR] while loop are processor operations, it uses all the processor resources
    Uint32 timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - *lastFrameTime);

    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(timeToWait);
    }

    *lastFrameTime = SDL_GetTicks(); // time in milliseconds from sdl init

}

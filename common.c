#include "common.h"

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

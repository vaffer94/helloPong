#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window*   window;
extern SDL_Renderer* renderer;

void shoutdown(void) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
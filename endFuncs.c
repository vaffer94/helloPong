#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window*   window;
extern SDL_Renderer* renderer;
extern SDL_Surface*  gHelloWorld;

void shoutdown(void) {

    // Deallocate surface
    if (gHelloWorld)
    {
        SDL_FreeSurface(gHelloWorld );
        gHelloWorld = NULL;
    }

    // objects are destroyed in reverse order of how they were created
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    // Don't worry about the screen surface, SDL_DestroyWindow will take care of it
    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    // Quit SDL subsystems
    SDL_Quit();
}
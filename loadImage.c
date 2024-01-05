#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "loadImage.h"

extern SDL_Surface*  gHelloWorld;

bool loadMedia()
{
    // Load splash image
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
        return false;
    }

    return true;
}
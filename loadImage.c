#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "loadImage.h"

extern SDL_Surface*  gHelloWorld;

bool loadMedia(char* imagePath)
{
    // Load splash image
    gHelloWorld = SDL_LoadBMP(imagePath);
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", imagePath, SDL_GetError());
        return false;
    }

    return true;
}
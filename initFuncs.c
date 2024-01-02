#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "initFuncs.h"

extern SDL_Window*   window;
extern SDL_Renderer* renderer;
extern Ball          ball;
extern bool          served;
extern Player        player1;
extern Player        player2;

/*******************************************************
 ****************** PUBLIC FUNCTIONS ******************
*******************************************************/

void printIntVal(int valToPrint)
{
    printf("Val: %d \n", valToPrint);
    printf("WIDTH: %d \n", WIDTH);
}

bool initialize(void) {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to install SDL: %s\n",
        SDL_GetError());

        return false;
    }

    window = SDL_CreateWindow("HelloPong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!window) {
        return false;
    }

    ball = makeBall(BALL_SIZE);
    player1 = makePlayer();
    player2 = makePlayer();

    return true;
}

/*******************************************************
 ****************** PRIVATE FUNCTIONS ******************
*******************************************************/

Player makePlayer(void)
{
    Player player = {
        .yPosition = HEIGHT / 2,
        .score     = 0,
    };

    return player;
}

bool coinFlip(void) {
    return rand() % 2 == 1 ? true : false;
}

Ball makeBall(int size) {
    const float speed = 120;

    Ball playBall = {
        .x      = WIDTH / 2 - size / 2,
        .y      = HEIGHT / 2 - size / 2,
        .xSpeed = speed * (coinFlip() ? 1 : -1),
        .ySpeed = speed * (coinFlip() ? 1 : -1),
        .size   = size,
    };

    return playBall;
}

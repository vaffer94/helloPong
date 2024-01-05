#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "updateFuncs.h"

extern SDL_Window*   window;
extern SDL_Renderer* renderer;
extern Ball          ball;
extern bool          served;
extern Player        player1;
extern Player        player2;

/*******************************************************
 ****************** PUBLIC FUNCTIONS ******************
*******************************************************/

void updateScore(int player, int points)
{
    served = false;

    if (player == 1)
    {
        player1.score += points;
    }

    if (player == 2)
    {
        player2.score += points;
    }

    char buf[30];
    int maxLen = sizeof(buf);
    char* ttl = "Player1: %d | Player2: %d";
    snprintf(buf, maxLen, ttl, player1.score, player2.score);
    SDL_SetWindowTitle(window, buf);
}

void update(float elapsed) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    updateBall(&ball, elapsed);
    renderBall(&ball);

    updatePlayers(elapsed);
    renderPlayers(renderer, player1, player2);

    // swap: back buffer that we populated become the front buffer
    SDL_RenderPresent(renderer);
}

/*******************************************************
 ****************** PRIVATE FUNCTIONS ******************
*******************************************************/
void renderBall(const Ball* ball) {
    int size = ball->size;
    float halfsize = (float)size / 2;

    SDL_Rect rect = {
        .x = ball->x - halfsize,
        .y = ball->y - halfsize,
        .w = size,
        .h = size,
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void updateBall(Ball* ball, float elapsed) {
    if (!served)
    {
        ball->x = WIDTH / 2;
        ball->y = HEIGHT / 2;
    }

    ball->x += ball->xSpeed * elapsed;
    ball->y += ball->ySpeed * elapsed;

    if (ball->x < 0 + BALL_SIZE)
    {
        /// ball->xSpeed = fabs(ball->xSpeed);
        updateScore(2, 100);
    }

    if (ball->x > WIDTH - BALL_SIZE)
    {
        // ball->xSpeed = -fabs(ball->xSpeed);
        updateScore(1, 100);
    }

    if (ball->y < 0 + BALL_SIZE)
    {
        ball->ySpeed = fabs(ball->ySpeed);
    }

    if (ball->y > HEIGHT - BALL_SIZE)
    {
        ball->ySpeed = -fabs(ball->ySpeed);
    }
}

void updatePlayers(float elapsed) {
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    if (keyboardState[SDL_SCANCODE_SPACE])
    {
        served = true;
    }

    if (keyboardState[SDL_SCANCODE_W])
    {
        player1.yPosition -= PLAYER_MOVE_SPEED * elapsed;
    }

    if (keyboardState[SDL_SCANCODE_S])
    {
        player1.yPosition += PLAYER_MOVE_SPEED * elapsed;
    }

    if (keyboardState[SDL_SCANCODE_UP])
    {
        player2.yPosition -= PLAYER_MOVE_SPEED * elapsed;
    }

    if (keyboardState[SDL_SCANCODE_DOWN])
    {
        player2.yPosition += PLAYER_MOVE_SPEED * elapsed;
    }

    if (player1.yPosition < PLAYER_HEIGHT / 2)
    {
        player1.yPosition = PLAYER_HEIGHT / 2;
    }

    if (player1.yPosition > HEIGHT - PLAYER_HEIGHT / 2)
    {
        player1.yPosition = HEIGHT - PLAYER_HEIGHT / 2;
    }

    if (player2.yPosition < PLAYER_HEIGHT / 2)
    {
        player2.yPosition = PLAYER_HEIGHT / 2;
    }

    if (player2.yPosition > HEIGHT - PLAYER_HEIGHT / 2)
    {
        player2.yPosition = HEIGHT - PLAYER_HEIGHT / 2;
    }

    SDL_Rect ballRect = {
        .x = ball.x - ball.size / 2,
        .y = ball.y - ball.size / 2,
        .w = ball.size,
        .h = ball.size,
    };

    SDL_Rect player1Rect = {
        .x = PLAYER_MARGIN,
        .y = (int)(player1.yPosition) - PLAYER_HEIGHT / 2,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
    };

    if (SDL_HasIntersection(&ballRect, &player1Rect))
    {
        // the ball goes to the right
        ball.xSpeed = fabs(ball.xSpeed);
    }

    SDL_Rect player2Rect = {
        .x = WIDTH - PLAYER_WIDTH - PLAYER_MARGIN,
        .y = (int)(player2.yPosition) - PLAYER_HEIGHT / 2,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
    };

    if (SDL_HasIntersection(&ballRect, &player2Rect))
    {
        // the ball goes to the left
        ball.xSpeed = - fabs(ball.xSpeed);
    }
}

void renderPlayers(SDL_Renderer* renderer, Player player1, Player player2)
{
    // render player 1 (left, red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect player1Rect = {
        .x = PLAYER_MARGIN,
        .y = (int)(player1.yPosition) - PLAYER_HEIGHT / 2,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
    };
    SDL_RenderFillRect(renderer, &player1Rect);

    // render player 2 (right, blue)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect player2Rect = {
        .x = WIDTH - PLAYER_WIDTH - PLAYER_MARGIN,
        .y = (int)(player2.yPosition) - PLAYER_HEIGHT / 2,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
    };
    SDL_RenderFillRect(renderer, &player2Rect);
}

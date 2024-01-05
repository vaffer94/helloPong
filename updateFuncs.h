#ifndef UPDATE_FUNCS_H_
#define UPDATE_FUNCS_H_

#include "constants.h"

void update(float);

void updateScore(int player, int points);

void renderBall(const Ball* ball);
void updateBall(Ball* ball, float elapsed);

void updatePlayers(float elapsed);
void renderPlayers(SDL_Renderer* renderer, Player player1, Player player2);

#endif // UPDATE_FUNCS_H_

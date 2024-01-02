#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WIDTH         = 640;
const int HEIGHT        = 480;
const int BALL_SIZE     = 10;
const int PLAYER_WIDTH  = 20;
const int PLAYER_HEIGHT = 75;
const int PLAYER_MARGIN = 10;

const float PLAYER_MOVE_SPEED = 150.0f;

typedef struct Ball {
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int size;
} Ball;

typedef struct Player {
    int score;
    float yPosition;
} Player;

SDL_Window*   window   = NULL;
SDL_Renderer* renderer = NULL;
Ball ball;
bool served = false;
Player player1;
Player player2;


//****************************************************************************

bool initialize(void);
void update(float);
void shoutdown(void);

Ball makeBall(int size);
void renderBall(const Ball* ball);
void updateBall(Ball* ball, float elapsed);

Player makePlayer(void);
void   updatePlayers(float elapsed);
void   renderPlayers(void);

void updateScore(int player, int points);

//****************************************************************************

int main(int argc, const char* argv[])
{
    printf("\n\nHello world!\n");
    printf("\U0001f984 - 👾\n\n");

    srand((unsigned int)time(NULL));
    atexit(shoutdown);

    if (!initialize()) {
        exit(1);
    }

    // SDL_Event event;

    // while(SDL_WaitEvent(&event)) {
    //     if (event.type == SDL_QUIT) {
    //         break;
    //     }
    // }

    bool quit = false;
    SDL_Event event;

    Uint32 lastTick = SDL_GetTicks();

    while (!quit){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

    Uint32 curTick = SDL_GetTicks();
    Uint32 diff = curTick - lastTick;
    float elapsed = diff / 1000.0f;

    update(elapsed);

    lastTick = curTick;

    }

    SDL_Quit();

    return 0;
}

//****************************************************************************

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

void update(float elapsed) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_Rect ballRect = {
    //     .x = WIDTH / 2 - BALL_SIZE / 2,
    //     .y = HEIGHT / 2 - BALL_SIZE / 2,
    //     .w = BALL_SIZE,
    //     .h = BALL_SIZE,
    // };

    // SDL_RenderFillRect(renderer, &ballRect);

    updateBall(&ball, elapsed);
    renderBall(&ball);

    updatePlayers(elapsed);
    renderPlayers(); 

    SDL_RenderPresent(renderer);
}

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

Player makePlayer(void)
{
    Player player = {
        .yPosition = HEIGHT / 2,
        .score     = 0,
    };

    return player;
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

void renderPlayers(void) {
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
    int len = snprintf(buf, maxLen, ttl, player1.score, player2.score);
    SDL_SetWindowTitle(window, buf);

    // TODOVF questa roba non scrive veramente il punteggio
    // char *ttl = "Player1: %d | Player2: %d";
    //  int len = snprintf(NULL, 0, ttl, player1.score, player2.score);
    //  char buf[len + 1];

    //  printf("len: %d \n", len);

    // snprintf(buf, len + 1, ttl, player1.score, player2.score);
    // SDL_SetWindowTitle(window, buf);
}

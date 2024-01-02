#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define WIDTH              640
#define HEIGHT             480
#define BALL_SIZE          10
#define PLAYER_WIDTH       20
#define PLAYER_HEIGHT      75
#define PLAYER_MARGIN      10
#define PLAYER_MOVE_SPEED  150.0F

typedef struct {
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int size;
} Ball;

typedef struct {
    int score;
    float yPosition;
} Player;

#endif //CONSTANTS_H_

#ifndef MODEL_H
#define MODEL_H
#include <SDL2/SDL.h>

typedef struct{
    int height;
    int width;
    int **gridArray;

}GRID;
typedef struct{
    int id;
    SDL_Color color;
}PLAYER;
typedef enum{
    isEmpty = 0,
    computerBlocked,
    p1Blocked,
    p2Blocked
}GRIDSTATE;
typedef enum{
    player1,
    player2
}PLAYERID;

void displayGrid(GRID *grid);
GRID initGridArray(int height, int width);
void freeGridArray(GRID grid);
PLAYER initPlayer(int playerId);
#endif // MODEL_H


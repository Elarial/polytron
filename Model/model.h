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
    int posX;
    int posY;
    int direction;
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
typedef enum{
    up,
    down,
    left,
    right
}DIRECTION;
typedef enum{
    p1DefaultposX = 10,
    p1DefaultposY = 10,
    p2DefaultposX = 500,
    p2DefaultposY = 400
}INITPOSITION;
typedef struct{
    GRID grid;
    PLAYER players[2];
    int nbPlayers;
}MODEL;
void displayGrid(GRID *grid);
GRID initGrid(int height, int width);
void freeGridArray(GRID grid);
PLAYER initPlayer(int playerId);
MODEL initModel();
int updateModel(MODEL *model,SDL_Renderer *renderer);
int updateDirection(MODEL *model, SDL_Keycode input);
int checkCollisions(MODEL *model);
void resetModel(MODEL *model);
#endif // MODEL_H


#ifndef MODEL_H
#define MODEL_H
#include <SDL2/SDL.h>

#define p1DefaultposX  (10)
#define p1DefaultposY (10)
#define p2DefaultposX (500)
#define p2DefaultposY (400)
/**
  *\brief Type représentant la grille de jeu.
  */
typedef struct{
    int height; /**< */
    int width;
    int **gridArray;

}GRID;
typedef struct{
    int id;
    char* name;
    int score;
    int posX;
    int posY;
    int direction;
    SDL_Keycode keyUp;
    SDL_Keycode keyDown;
    SDL_Keycode keyLeft;
    SDL_Keycode keyRight;
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


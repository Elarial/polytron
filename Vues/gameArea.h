#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <SDL2/SDL.h>
#include "../Controller/controller.h"
#include "../Model/model.h"

typedef struct{
    SDL_Texture *backgroundTexture;
    char *pathBackground;

}GAMEAREA;
GAMEAREA initGameArea(SDLcontext *context);
int setRenderDrawColorFromPlayer(PLAYER *player,SDL_Renderer *renderer);
int upgradeGridView(GRID *grid,PLAYER *player[],int nbPlayer, SDL_Renderer *renderer);
#endif // GAMEAREA_H


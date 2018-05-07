#include "gameArea.h"
#include <SDL2/SDL.h>
#include "../Controller/tools.h"

GAMEAREA initGameArea (SDLcontext *context){
    SDL_Texture *background = NULL;
    char *pathBackground = "sonicpaper.bmp";
}
int upgradeGridView(GRID *grid,PLAYER *player[],int nbPlayer,SDL_Renderer *renderer){
    for (int p = 0; p < nbPlayer; ++p) {

        if(setRenderDrawColorFromPlayer(player[p],renderer)!=EXIT_SUCCESS){
            return(EXIT_FAILURE);
        }
        for (int i = 0; i < grid->height; ++i) {
            for (int j = 0;  j< grid->width; j++) {
                if((player[p]->id == player1 && grid->gridArray[i][j] == p1Blocked)||(player[p]->id == player2 && grid->gridArray[i][j] == p2Blocked)){
                    if(SDL_RenderDrawPoint(renderer,grid->width,grid->height)!=EXIT_SUCCESS){
                        logSDLError("Erreur lors du dessin des points");
                        return(EXIT_FAILURE);
                    }
                }
            }
        }
    }
    return(EXIT_SUCCESS);
}
int setRenderDrawColorFromPlayer(PLAYER *player,SDL_Renderer *renderer){
    if (SDL_SetRenderDrawColor(renderer,player->color.r,player->color.g,player->color.b,player->color.a)!=EXIT_SUCCESS){
        logSDLError("Erreur lors du reglage de la couleur par defaut pour dessiner");
        return(EXIT_FAILURE);
    }else{
        return(EXIT_SUCCESS);
    }
}


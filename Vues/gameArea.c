#include "gameArea.h"
#include "../Controller/tools.h"


GAMEAREA initGameArea (SDLcontext *context){
    SDL_Texture *background = NULL;
    char *pathBackground = "sonicpaper.bmp";
}

int completeUpdateGridView(MODEL *model,SDL_Renderer *renderer){
    for (int p = 0; p < model->nbPlayers; ++p) {

        if(setRenderDrawColorFromPlayer(&(model->players[p]),renderer)!=EXIT_SUCCESS){
            return(EXIT_FAILURE);
        }
        for (int i = 0; i < model->grid.height; ++i) {
            for (int j = 0;  j< model->grid.width; j++) {
                if((model->players[p].id == player1 && model->grid.gridArray[i][j] == p1Blocked)||(model->players[p].id == player2 && model->grid.gridArray[i][j] == p2Blocked)){
                    if(SDL_RenderDrawPoint(renderer,i,j)!=EXIT_SUCCESS){
                        logSDLError("Erreur lors du dessin des points");
                        return(EXIT_FAILURE);
                    }
                }
            }
        }
    }
    //Retour au RenderDrawColor initial
    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    return(EXIT_SUCCESS);
}
int partialUpdateGridView(MODEL *model,SDL_Renderer *renderer){
    for (int p = 0; p < model->nbPlayers; ++p) {

        if(setRenderDrawColorFromPlayer(&(model->players[p]),renderer)!=EXIT_SUCCESS){
            return(EXIT_FAILURE);
        }
                if((model->players[p].id == player1 && model->grid.gridArray[model->players[p].posX][model->players[p].posY] == p1Blocked)
                        ||(model->players[p].id == player2 && model->grid.gridArray[model->players[p].posX][model->players[p].posY] == p2Blocked)){
                    if(SDL_RenderDrawPoint(renderer,model->players[p].posX,model->players[p].posY)!=EXIT_SUCCESS){
                        logSDLError("Erreur lors du dessin des points");
                        return(EXIT_FAILURE);
            }
        }
    }
    //Retour au RenderDrawColor initial
    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
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


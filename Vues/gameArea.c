#include "gameArea.h"
#include "../Controller/tools.h"


GAMEAREA initGameArea (SDLcontext *context){
    SDL_Texture *background = NULL;
    char *pathBackground = "sonicpaper.bmp";
}
CHAR_ANIMATION initCharAnimation(char *spriteSheetName,SDL_Renderer *renderer){
    int height = 26;
    int width1 = 16;
    int witdh2 = 20;
    CHAR_ANIMATION animation;
    animation.spritesTexture = loadTextureImg(spriteSheetName,renderer);
    if(animation.spritesTexture == NULL){
        logSDLError("impossible de charger les sprites");
    }
    animation.activeFrame = 0;
    animation.spriteSheetName = spriteSheetName;
    //initialisation de la hauteur des rectangles
    animation.frames[up][0].h=height;
    animation.frames[up][1].h=height;
    animation.frames[up][2].h=height;
    animation.frames[left][0].h=height;
    animation.frames[left][1].h=height;
    animation.frames[left][2].h=height;
    animation.frames[down][0].h=height;
    animation.frames[down][1].h=height;
    animation.frames[down][2].h=height;
    animation.frames[right][0].h=height;
    animation.frames[right][1].h=height;
    animation.frames[right][2].h=height;
    //initialisation de la largeur des rectangles
    animation.frames[up][0].w=width1;
    animation.frames[up][1].w=width1;
    animation.frames[up][2].w=width1;
    animation.frames[left][0].w=witdh2;
    animation.frames[left][1].w=witdh2;
    animation.frames[left][2].w=witdh2;
    animation.frames[down][0].w=width1;
    animation.frames[down][1].w=width1;
    animation.frames[down][2].w=width1;
    animation.frames[right][0].w=witdh2;
    animation.frames[right][1].w=witdh2;
    animation.frames[right][2].w=witdh2;
    //initialisation de de la position x des rectangles
    animation.frames[up][0].x=0;
    animation.frames[up][1].x=animation.frames[up][0].w;
    animation.frames[up][2].x=animation.frames[up][0].w + animation.frames[up][1].w ;
    animation.frames[left][0].x=0;
    animation.frames[left][1].x=animation.frames[left][0].w;
    animation.frames[left][2].x=animation.frames[left][0].w + animation.frames[left][1].w ;
    animation.frames[down][0].x=0;
    animation.frames[down][1].x=animation.frames[down][0].w;
    animation.frames[down][2].x=animation.frames[down][0].w + animation.frames[down][1].w ;
    animation.frames[right][0].x=0;
    animation.frames[right][1].x=animation.frames[right][0].w;
    animation.frames[right][2].x=animation.frames[right][0].w + animation.frames[right][1].w ;
    //initialisation de la position y des rectangles
    animation.frames[up][0].y=0;
    animation.frames[up][1].y=0;
    animation.frames[up][2].y=0;
    animation.frames[left][0].y=animation.frames[up][0].h + animation.frames[right][0].h + animation.frames[down][0].h;
    animation.frames[left][1].y=animation.frames[up][1].h + animation.frames[right][1].h + animation.frames[down][1].h;
    animation.frames[left][2].y=animation.frames[up][2].h + animation.frames[right][2].h + animation.frames[down][2].h;
    animation.frames[down][0].y=animation.frames[up][0].h + animation.frames[right][0].h;
    animation.frames[down][1].y=animation.frames[up][1].h + animation.frames[right][1].h;
    animation.frames[down][2].y=animation.frames[up][2].h + animation.frames[right][2].h;
    animation.frames[right][0].y=animation.frames[up][0].h;
    animation.frames[right][1].y=animation.frames[up][1].h;
    animation.frames[right][2].y=animation.frames[up][2].h;
    return animation;
}

int completeUpdateGridView(MODEL *model,SDL_Renderer *renderer){

    for (int i = 0; i < model->grid.height; ++i) {
        for (int j = 0;  j< model->grid.width; j++) {
            if(model->grid.gridArray[i][j] == p1Blocked){
                if(setRenderDrawColorFromPlayer(&(model->players[player1]),renderer) ==EXIT_SUCCESS){
                    if(SDL_RenderDrawPoint(renderer,i,j)!=EXIT_SUCCESS){
                        logSDLError("Erreur lors du dessin des points");
                        return(EXIT_FAILURE);
                    }

                }
            }else if( model->grid.gridArray[i][j] == p2Blocked){
                if(setRenderDrawColorFromPlayer(&(model->players[player2]),renderer) !=EXIT_SUCCESS && SDL_RenderDrawPoint(renderer,i,j)!=EXIT_SUCCESS){
                    logSDLError("Erreur lors du dessin des points");
                    return(EXIT_FAILURE);
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


#include "gameArea.h"
#include "../Controller/tools.h"


GAMEAREA initGameArea (SDLcontext *context){
    GAMEAREA gameArea;
    gameArea.fontColor.r=255,gameArea.fontColor.g=0,gameArea.fontColor.b=0,gameArea.fontColor.a=SDL_ALPHA_OPAQUE;
    gameArea.font = getFontFromFile("NiseSegaSonic.TTF",40);
    gameArea.loadingTexture = loadTextureImg("vsloadin.png",*(context->renderer));
    gameArea.backgroundTexture = loadTextureImg("gamebackground.jpg",*(context->renderer));
    gameArea.animations[player1] = initCharAnimation("sonic.png",*(context->renderer),26,16,20);
    gameArea.animations[player2] = initCharAnimation("tails.png",*(context->renderer),22,22,22);
    return gameArea;

}

ANIMATION initCharAnimation(char *spriteSheetName,SDL_Renderer *renderer,int height,int widths,int widthl){
    ANIMATION animation;
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
    animation.frames[up][0].w=widths;
    animation.frames[up][1].w=widths;
    animation.frames[up][2].w=widths;
    animation.frames[left][0].w=widthl;
    animation.frames[left][1].w=widthl;
    animation.frames[left][2].w=widthl;
    animation.frames[down][0].w=widths;
    animation.frames[down][1].w=widths;
    animation.frames[down][2].w=widths;
    animation.frames[right][0].w=widthl;
    animation.frames[right][1].w=widthl;
    animation.frames[right][2].w=widthl;
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
void renderGameArea(GAMEAREA *gameArea,SDLcontext *context,MODEL *model){
    SDL_Texture *countDownText;
    SDL_Rect playerloadingRect[2];
    SDL_Texture *playerNameTexture[2];
    for (int i = 0; i < model->nbPlayers; ++i) {
        playerNameTexture[i] = renderText(model->players[i].name,gameArea->fontColor,*(context->renderer),gameArea->font);
        playerloadingRect[i] = createRectFromTexture(playerNameTexture[i]);
        playerloadingRect[i].x = i*350 + 50;
        playerloadingRect[i].y = i*350 + 50;
    }
    for (int i = 0; i < 2; ++i) {
        SDL_RenderClear(*(context->renderer));
        countDownText = (i == 0) ? renderText("%EADY ?",gameArea->fontColor,*(context->renderer),gameArea->font) : renderText("GO @",gameArea->fontColor,*(context->renderer),gameArea->font);
        gameArea->fontRect = createRectFromTexture(countDownText);
        gameArea->fontRect.x=context->width/2-gameArea->fontRect.w/2;
        gameArea->fontRect.y=context->height/2-gameArea->fontRect.h/2;
        SDL_RenderCopy(*(context->renderer),gameArea->loadingTexture,NULL,NULL);
        SDL_RenderCopy(*(context->renderer),countDownText,NULL,&(gameArea->fontRect));
         for (int p = 0; p < model->nbPlayers; ++p){
             SDL_RenderCopy(*(context->renderer),playerNameTexture[p],NULL,&(playerloadingRect[p]));
         }
        SDL_RenderPresent(*(context->renderer));
        SDL_Delay(2000);
    }

    SDL_RenderClear(*(context->renderer));

    SDL_RenderCopy(*(context->renderer),gameArea->backgroundTexture,NULL,NULL);
    SDL_SetRenderDrawColor(*(context->renderer),255,0,0,SDL_ALPHA_OPAQUE);
    for (int i = 0; i < 640; ++i) {
        for (int j = 0; j < 480; ++j) {
            if(model->grid.gridArray[i][j]==computerBlocked){
                SDL_RenderDrawPoint(*(context->renderer),i,j);
            }
        }
    }
    SDL_SetRenderDrawColor(*(context->renderer),0,0,0,SDL_ALPHA_OPAQUE);
}

void nextAnimationStep(GAMEAREA *gameArea,MODEL *model,SDL_Renderer *renderer){

    for (int i = 0; i < model->nbPlayers; ++i) {
        gameArea->animations[i].activeFrame  += 1;
        gameArea->animations[i].activeFrame %= 9;
        SDL_RenderCopy(renderer,gameArea->animations[i].spritesTexture,&(gameArea->animations[i].frames[model->players[i].direction][gameArea->animations[i].activeFrame/3]),&(model->players[i].rect));
    }
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
                if(setRenderDrawColorFromPlayer(&(model->players[player2]),renderer) == EXIT_SUCCESS){
                    if( SDL_RenderDrawPoint(renderer,i,j)!=EXIT_SUCCESS){
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
        SDL_RenderFillRect(renderer,&(model->players[p].rect));
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


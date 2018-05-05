#include "mainMenu.h"
#include <SDL2/SDL.h>
#include "../Controller/tools.h"

MAINMENU initMainMenu(SDLcontext *context){
    SDL_Texture *backgroundTexture = NULL;
    SDL_Texture *player1Texture = NULL;
    SDL_Texture *player2Texture = NULL;
    SDL_Texture *playerVsAiTexture = NULL;
    SDL_Texture *optionsTexture = NULL;
    SDL_Texture *scoresTexture = NULL;
    SDL_Color   defaultColor={255,255,255,100};
    SDL_Color   selectedColor={255,255,255,100};
    int fontSize =20;
    char* pathBackground = "sonic_1_1991.jpg";
    char* pathTTF = "NiseSega.TTF";
    backgroundTexture = loadTextureImg(pathBackground,context->renderer);
    player1Texture = renderText("SOLO",pathTTF,defaultColor,fontSize,context->renderer);
    SDL_Rect player1Rect = createRectFromTexture(player1Texture);
    player2Texture = renderText("VERSUS",pathTTF,defaultColor,fontSize,context->renderer);
    SDL_Rect player2Rect = createRectFromTexture(player2Texture);
    playerVsAiTexture = renderText("VERSUS IA",pathTTF,defaultColor,fontSize,context->renderer);
    SDL_Rect playerVsAiRect = createRectFromTexture(playerVsAiTexture);
    optionsTexture = renderText("OPTIONS",pathTTF,defaultColor,fontSize,context->renderer);
    SDL_Rect optionsRect = createRectFromTexture(optionsTexture);
    scoresTexture = renderText("SCORES",pathTTF,defaultColor,fontSize,context->renderer);
    SDL_Rect scoresRect = createRectFromTexture(scoresTexture) ;
    //Todo: outline
    int xCenter,yCenter,offsetInit,offset;
    xCenter = context->width/2;
    yCenter = context->height/2;
    offsetInit = 150;
    offset = 20;
    player1Rect.x=xCenter - player1Rect.w/2 ,player1Rect.y=yCenter - player1Rect.h/2+offsetInit;
    player2Rect.x=xCenter - player2Rect.w/2,player2Rect.y=yCenter - player2Rect.h/2+offsetInit+offset;
    playerVsAiRect.x=xCenter - playerVsAiRect.w/2,playerVsAiRect.y=yCenter - playerVsAiRect.h/2+offsetInit+2*offset;
    optionsRect.x=xCenter - optionsRect.w/2,optionsRect.y=yCenter - optionsRect.h/2+offsetInit+3*offset;
    scoresRect.x=xCenter - scoresRect.w/2,scoresRect.y=yCenter - scoresRect.h/2+offsetInit+4*offset;

    MAINMENU mainMenu = {
        backgroundTexture,
        player1Texture,
        player1Rect,
        player2Texture,
        player2Rect,
        playerVsAiTexture,
        playerVsAiRect,
        optionsTexture,
        optionsRect,
        scoresTexture,
        scoresRect,
        defaultColor,
        selectedColor,
        fontSize
    };
    return mainMenu;
}

int renderMainMenu(MAINMENU *mainmenu,SDLcontext *context){
    //TODO : Build le renderer avec une boucle for.
    //TODO : check la réussite de SDL_RenderCopy.
    SDL_RenderCopy(*(context->renderer),mainmenu->backgroundTexture,NULL,NULL);
    //possible problème d'acccès aux pointeurs.
    if(SDL_RenderCopy(*(context->renderer),mainmenu->player1Texture,NULL,&(mainmenu->player1Rect))!=EXIT_SUCCESS){
        printf("echec de copie sur le rendu");
    }
    SDL_RenderCopy(*(context->renderer),mainmenu->player2Texture,NULL,&(mainmenu->player2Rect));
    SDL_RenderCopy(*(context->renderer),mainmenu->playerVsAiTexture,NULL,&(mainmenu->playerVsAiRect));
    SDL_RenderCopy(*(context->renderer),mainmenu->optionsTexture,NULL,&(mainmenu->optionsRect));
    SDL_RenderCopy(*(context->renderer),mainmenu->scoresTexture,NULL,&(mainmenu->scoresRect));
    return(EXIT_SUCCESS);
}

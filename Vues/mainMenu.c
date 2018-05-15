#include "mainMenu.h"
#include "../Controller/tools.h"

MAINMENU initMainMenu(SDLcontext *context){
    SDL_Texture *backgroundTexture = NULL;
    SDL_Texture *player1Texture = NULL;
    SDL_Texture *player2Texture = NULL;
    SDL_Texture *playerVsAiTexture = NULL;
    SDL_Texture *optionsTexture = NULL;
    SDL_Texture *scoresTexture = NULL;
    SDL_Color   defaultColor={255,255,255,SDL_ALPHA_OPAQUE};
    SDL_Color   selectedColor={128,82,82,SDL_ALPHA_OPAQUE};
    int fontSize =20;
    char* pathBackground = "sonic_1_1991.jpg";
    char* pathTTF = "NiseSega.TTF";
    char* player1Text = "SOLO";
    char* player2Text = "VERSUS";
    char* playerVsAiText = "VERSUS IA";
    char* optionsText = "OPTIONS";
    char* scoresText = "SCORES";
    backgroundTexture = loadTextureImg(pathBackground,*(context->renderer));
    player1Texture = renderText(player1Text,pathTTF,defaultColor,fontSize,*(context->renderer));
    SDL_Rect player1Rect = createRectFromTexture(player1Texture);
    player2Texture = renderText(player2Text,pathTTF,defaultColor,fontSize,*(context->renderer));
    SDL_Rect player2Rect = createRectFromTexture(player2Texture);
    playerVsAiTexture = renderText(playerVsAiText,pathTTF,defaultColor,fontSize,*(context->renderer));
    SDL_Rect playerVsAiRect = createRectFromTexture(playerVsAiTexture);
    optionsTexture = renderText(optionsText,pathTTF,defaultColor,fontSize,*(context->renderer));
    SDL_Rect optionsRect = createRectFromTexture(optionsTexture);
    scoresTexture = renderText(scoresText,pathTTF,defaultColor,fontSize,*(context->renderer));
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
        player1Text,
        player2Texture,
        player2Rect,
        player2Text,
        playerVsAiTexture,
        playerVsAiRect,
        playerVsAiText,
        optionsTexture,
        optionsRect,
        optionsText,
        scoresTexture,
        scoresRect,
        scoresText,
        defaultColor,
        selectedColor,
        pathBackground,
        pathTTF,
        fontSize,

    };
    return mainMenu;
}

int renderMainMenu(MAINMENU *mainMenu,int ctr,SDL_Renderer *renderer){
    if(ctr<mainMenuSolo || ctr>mainMenuScores){
        logSDLError("Index de position invalide");
        return(EXIT_FAILURE);
    }else{
        //Changement de la couleur du texte en fontion de l'input
        switch (ctr) {
        case mainMenuSolo:
            mainMenu->player1Texture=renderText(mainMenu->player1Text,mainMenu->pathTTF,mainMenu->selectedColor,mainMenu->fontSize,renderer);
            mainMenu->player2Texture=renderText(mainMenu->player2Text,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            mainMenu->scoresTexture=renderText(mainMenu->scoresText,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            break;
        case mainMenuPvp:
            mainMenu->player2Texture=renderText(mainMenu->player2Text,mainMenu->pathTTF,mainMenu->selectedColor,mainMenu->fontSize,renderer);
            mainMenu->player1Texture=renderText(mainMenu->player1Text,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            mainMenu->playerVsAiTexture=renderText(mainMenu->playerVsAiText,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            break;
        case mainMenuPvAi:
            mainMenu->playerVsAiTexture=renderText(mainMenu->playerVsAiText,mainMenu->pathTTF,mainMenu->selectedColor,mainMenu->fontSize,renderer);
            mainMenu->player2Texture=renderText(mainMenu->player2Text,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            mainMenu->optionsTexture=renderText(mainMenu->optionsText,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            break;
        case mainMenuOptions:
            mainMenu->optionsTexture=renderText(mainMenu->optionsText,mainMenu->pathTTF,mainMenu->selectedColor,mainMenu->fontSize,renderer);
            mainMenu->playerVsAiTexture=renderText(mainMenu->playerVsAiText,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            mainMenu->scoresTexture=renderText(mainMenu->scoresText,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            break;
        case mainMenuScores:
            mainMenu->scoresTexture=renderText(mainMenu->scoresText,mainMenu->pathTTF,mainMenu->selectedColor,mainMenu->fontSize,renderer);
            mainMenu->optionsTexture=renderText(mainMenu->optionsText,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
            mainMenu->player1Texture=renderText(mainMenu->player1Text,mainMenu->pathTTF,mainMenu->defaultColor,mainMenu->fontSize,renderer);
        default:
            break;
        }
    }

    //TODO : Build le renderer avec une boucle for.

    //Copie sur le rendu.
    if(SDL_RenderCopy(renderer,mainMenu->backgroundTexture,NULL,NULL)!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du background sur le rendu");
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,mainMenu->player1Texture,NULL,&(mainMenu->player1Rect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du texte player 1 sur le rendu");
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,mainMenu->player2Texture,NULL,&(mainMenu->player2Rect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du texte player 2 sur le rendu");
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,mainMenu->playerVsAiTexture,NULL,&(mainMenu->playerVsAiRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du texte PvAi sur le rendu");
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,mainMenu->optionsTexture,NULL,&(mainMenu->optionsRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du texte Option sur le rendu");
        return(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer,mainMenu->scoresTexture,NULL,&(mainMenu->scoresRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du texte score sur le rendu");
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

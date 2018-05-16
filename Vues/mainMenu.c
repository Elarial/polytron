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
    TTF_Font *font = getFontFromFile(pathTTF,fontSize);
    backgroundTexture = loadTextureImg(pathBackground,*(context->renderer));
    player1Texture = renderText(player1Text,defaultColor,*(context->renderer),font);
    SDL_Rect player1Rect = createRectFromTexture(player1Texture);
    player2Texture = renderText(player2Text,defaultColor,*(context->renderer),font);
    SDL_Rect player2Rect = createRectFromTexture(player2Texture);
    playerVsAiTexture = renderText(playerVsAiText,defaultColor,*(context->renderer),font);
    SDL_Rect playerVsAiRect = createRectFromTexture(playerVsAiTexture);
    optionsTexture = renderText(optionsText,defaultColor,*(context->renderer),font);
    SDL_Rect optionsRect = createRectFromTexture(optionsTexture);
    scoresTexture = renderText(scoresText,defaultColor,*(context->renderer),font);
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
        font

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
            mainMenu->player1Texture=renderText(mainMenu->player1Text,mainMenu->selectedColor,renderer,mainMenu->font);
            mainMenu->player2Texture=renderText(mainMenu->player2Text,mainMenu->defaultColor,renderer,mainMenu->font);
            mainMenu->scoresTexture=renderText(mainMenu->scoresText,mainMenu->defaultColor,renderer,mainMenu->font);
            break;
        case mainMenuPvp:
            mainMenu->player2Texture=renderText(mainMenu->player2Text,mainMenu->selectedColor,renderer,mainMenu->font);
            mainMenu->player1Texture=renderText(mainMenu->player1Text,mainMenu->defaultColor,renderer,mainMenu->font);
            mainMenu->playerVsAiTexture=renderText(mainMenu->playerVsAiText,mainMenu->defaultColor,renderer,mainMenu->font);
            break;
        case mainMenuPvAi:
            mainMenu->playerVsAiTexture=renderText(mainMenu->playerVsAiText,mainMenu->selectedColor,renderer,mainMenu->font);
            mainMenu->player2Texture=renderText(mainMenu->player2Text,mainMenu->defaultColor,renderer,mainMenu->font);
            mainMenu->optionsTexture=renderText(mainMenu->optionsText,mainMenu->defaultColor,renderer,mainMenu->font);
            break;
        case mainMenuOptions:
            mainMenu->optionsTexture=renderText(mainMenu->optionsText,mainMenu->selectedColor,renderer,mainMenu->font);
            mainMenu->playerVsAiTexture=renderText(mainMenu->playerVsAiText,mainMenu->defaultColor,renderer,mainMenu->font);
            mainMenu->scoresTexture=renderText(mainMenu->scoresText,mainMenu->defaultColor,renderer,mainMenu->font);
            break;
        case mainMenuScores:
            mainMenu->scoresTexture=renderText(mainMenu->scoresText,mainMenu->selectedColor,renderer,mainMenu->font);
            mainMenu->optionsTexture=renderText(mainMenu->optionsText,mainMenu->defaultColor,renderer,mainMenu->font);
            mainMenu->player1Texture=renderText(mainMenu->player1Text,mainMenu->defaultColor,renderer,mainMenu->font);
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

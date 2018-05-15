#include "scores.h"

SCORES_DISPLAY initScoresDisplay(SDLcontext *context,SCORE scores[10]){
    SCORES_DISPLAY scoresDisplay={0};
    int fontSize = 20;
    scoresDisplay.backgroundTexture = loadTextureImg("menubackground.png",*(context->renderer));
    char *fontFile ="NiseSega.TTF";
    SDL_Color defaultColor = {255,255,255,SDL_ALPHA_OPAQUE};
    SDL_Color selectedColor = {128,82,82,SDL_ALPHA_OPAQUE};

    //Création et placement des textes statiques
    scoresDisplay.returnValue = initTexte("RETOUR AU MENU PRINCIPAL",fontFile,selectedColor,fontSize,*(context->renderer));
    scoresDisplay.returnValue.textRect.y = context->height - 50;
    scoresDisplay.returnValue.textRect.x = context->width/2 - scoresDisplay.returnValue.textRect.w/2;
    scoresDisplay.highScores = initTexte("MEILLEURS SCORES",fontFile,defaultColor,fontSize,*(context->renderer));
    scoresDisplay.highScores.textRect.y = 10;
    scoresDisplay.highScores.textRect.x = context->width/2 - scoresDisplay.highScores.textRect.w/2;
    scoresDisplay.position = initTexte("POSITION",fontFile,defaultColor,fontSize,*(context->renderer));
    scoresDisplay.position.textRect.y = 50;
    scoresDisplay.position.textRect.x = 0;
    scoresDisplay.name = initTexte("NOM",fontFile,defaultColor,fontSize,*(context->renderer));
    scoresDisplay.name.textRect.y = 50;
    scoresDisplay.name.textRect.x = context->width/2 - scoresDisplay.name.textRect.w/2;
    scoresDisplay.score = initTexte("score",fontFile,defaultColor,fontSize,*(context->renderer));
    scoresDisplay.score.textRect.y = 50;
    scoresDisplay.score.textRect.x = context->width - scoresDisplay.score.textRect.w;
    updateScores(scores,&(scoresDisplay),context);
    return scoresDisplay;
}
int renderScoresDisplay(SCORES_DISPLAY scoresDisplay,SDL_Renderer *renderer){

    if(SDL_RenderCopy(renderer,scoresDisplay.backgroundTexture,NULL,NULL)!=EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,scoresDisplay.returnValue.textTexture,NULL,&(scoresDisplay.returnValue.textRect))!=EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,scoresDisplay.highScores.textTexture,NULL,&(scoresDisplay.highScores.textRect))!=EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,scoresDisplay.position.textTexture,NULL,&(scoresDisplay.position.textRect))!=EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,scoresDisplay.name.textTexture,NULL,&(scoresDisplay.name.textRect))!=EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    if(SDL_RenderCopy(renderer,scoresDisplay.score.textTexture,NULL,&(scoresDisplay.score.textRect))!=EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }

    for (int i = 0; i < 30; ++i) {
        if(scoresDisplay.scoresRects[i].h>0 && scoresDisplay.scoresRects[i].w>0){
            if(SDL_RenderCopy(renderer,scoresDisplay.scoresTextures[i],NULL,&scoresDisplay.scoresRects[i])!=EXIT_SUCCESS){
                return(EXIT_FAILURE);
            }
        }
    }
    return(EXIT_SUCCESS);
}
void updateScores(SCORE scores[10],SCORES_DISPLAY *scoresDisplay,SDLcontext *context){
    int nbElements = 30;
    char* fontFile = "NiseSega.TTF";
    SDL_Color defaultColor = {255,255,255,SDL_ALPHA_OPAQUE};
    int fontSize = 20;
    int header = 100;
    int footer = 100;
    int heightSize = context->height - (header+footer);
    int widthSize = context->width;


    char messages[nbElements][30];
    for (int i = 0; i < 10; ++i) {
        //Transformation des entiers en string
        sprintf(messages[3*i],"%d",scores[i].position);
        strcpy(messages[(3*i)+1],scores[i].name);
        sprintf(messages[(3*i)+2],"%d",scores[i].score);
    }
    renderTexts(scoresDisplay->scoresTextures,messages,fontFile,defaultColor,fontSize,*(context->renderer),nbElements);

    //Création, placement et rendu des rectangles d'affichage.
    int j = 0;
    for (int i = 0; i < nbElements; ++i) {
        scoresDisplay->scoresRects[i]=createRectFromTexture(scoresDisplay->scoresTextures[i]);
        //Placement vertical par subdivision de la taille affecté à l'affichage
        scoresDisplay->scoresRects[i].y = header+(heightSize*i/3/10);
        switch (j) {
        case 0:
            //Placement horizontal à gauche.
            scoresDisplay->scoresRects[i].x = scoresDisplay->position.textRect.w/2;
            break;
        case 1:
            //Placement horizontal au centre.
            scoresDisplay->scoresRects[i].x = widthSize/2 - scoresDisplay->scoresRects[i].w/2 ;
            break;
        case 2:
            //placement horizontal à droite.
            scoresDisplay->scoresRects[i].x = widthSize - scoresDisplay->score.textRect.w/2 - scoresDisplay->scoresRects[i].w/2 ;
            break;
        default:
            break;
        }
        j++;
        j %= 3;

    }
}

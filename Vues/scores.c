#include "scores.h"

SCORES_DISPLAY initScoresDisplay(SDLcontext *context,SCORE scores[10]){
    SCORES_DISPLAY scoresDisplay;
    scoresDisplay.backgroundTexture = loadTextureImg("sonic_1_1991.jpg",*(context->renderer));
    char *fontFile ="NiseSega.TTF";
    SDL_Color defaultColor = {255,255,255,SDL_ALPHA_OPAQUE};
    SDL_Color selectedColor = {128,82,82,SDL_ALPHA_OPAQUE};
    int fontSize = 20;
    int nbElements = 30;
    int header = 100;
    int footer = 100;
    int heightSize = context->height - (header+footer);
    int widthSize = context->width;

    char messages[nbElements][30];
    for (int i = 0; i < 10; ++i) {
        printf("position : %d\n",scores[i].position);
        printf("position : %s\n",scores[i].name);
        printf("position : %d\n",scores[i].score);
        sprintf(messages[3*i],"%d",scores[i].position);
        strcpy(messages[(3*i)+1],scores[i].name);
        sprintf(messages[(3*i)+2],"%d",scores[i].score);
    }
    renderTexts(scoresDisplay.scoresTextures,messages,fontFile,defaultColor,fontSize,*(context->renderer),nbElements);
    SDL_RenderCopy(*(context->renderer),scoresDisplay.backgroundTexture,NULL,NULL);
    //Création, placement et rendu des rectangles d'affichage.
    int j = 0;
    for (int i = 0; i < nbElements; ++i) {
        scoresDisplay.scoresRects[i]=createRectFromTexture(scoresDisplay.scoresTextures[i]);
        //Placement vertical par subdivision de la taille affecté à l'affichage
        scoresDisplay.scoresRects[i].y = header+(heightSize*i/3/10);
        switch (j) {
        case 0:
            //Placement horizontal à gauche.
            scoresDisplay.scoresRects[i].x = 0;
            break;
        case 1:
            //Placement horizontal au centre.
            scoresDisplay.scoresRects[i].x = widthSize/2 - scoresDisplay.scoresRects[i].w/2 ;
            break;
        case 2:
            //placement horizontal à droite.
            scoresDisplay.scoresRects[i].x = widthSize - scoresDisplay.scoresRects[i].w ;
            break;
        default:
            break;
        }
        j++;
        j %= 3;
        SDL_RenderCopy(*(context->renderer),scoresDisplay.scoresTextures[i],NULL,&scoresDisplay.scoresRects[i]);
    }
    return scoresDisplay;
}

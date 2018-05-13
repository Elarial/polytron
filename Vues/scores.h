#ifndef SCORES_H
#define SCORES_H
#include "../Model/scoresmodel.h"
#include "../Controller/tools.h"

typedef struct{
    SDL_Texture *backgroundTexture;
    SDL_Texture *scoresTextures[30];
    SDL_Rect scoresRects[30];
}SCORES_DISPLAY;
SCORES_DISPLAY initScoresDisplay(SDLcontext *context,SCORE scores[10]);

#endif // SCORES_H


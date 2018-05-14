#ifndef SCORES_H
#define SCORES_H
#include "../Model/scoresmodel.h"
#include "../Controller/tools.h"

typedef struct{
    SDL_Texture *backgroundTexture;
    SDL_Texture *scoresTextures[30];
    SDL_Rect scoresRects[30];
    TEXT returnValue;
    TEXT highScores;
    TEXT position;
    TEXT name;
    TEXT score;
}SCORES_DISPLAY;
SCORES_DISPLAY initScoresDisplay(SDLcontext *context,SCORE scores[10]);
int renderScoresDisplay(SCORES_DISPLAY scoresDisplay,SDL_Renderer *renderer);
void updateScores(SCORE scores[10],SCORES_DISPLAY *scoresDisplay,SDLcontext *context);
#endif // SCORES_H


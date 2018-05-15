#ifndef SCOREMODEL_H
#define SCOREMODEL_H
#include <stdio.h>
#include "../Controller/tools.h"
#include "model.h"
typedef struct{
    int position;
    char name[10];
    int score;
}SCORE;
int readScoreFile(SCORE scores[],FILE *scoreFile);
int writeScoreFile(SCORE scores[],FILE *scoreFile);
SCORE createScore (PLAYER *player);
void insertScore(SCORE scores[10],SCORE score);
void initScoreforTests(SCORE scores[10]);
void updateScoresMenu(int *activeView,SDL_Keycode input,GAMEMUSIC *gameMusic);
#endif // SCOREMODEL_H


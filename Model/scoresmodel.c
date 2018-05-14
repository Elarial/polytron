#include "scoresmodel.h"

void updateScoresMenu(int *activeView,SDL_Keycode input){
    if(input == SDLK_a){
        *activeView = main_menu;
    }
}
int readScoreFile(SCORE scores[],FILE *scoreFile){
    scoreFile = fopen("scores.txt","r");
    if(scoreFile == NULL){
        logSDLError("Impossible d'ouvrir le fichier score pour la lecture.");
        return(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; ++i) {
        fread(&scores[i],sizeof(SCORE),1,scoreFile);
    }

    if(fclose(scoreFile)!=EXIT_SUCCESS){
        logSDLError("Impossible de fermer le fichier après lecture");
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

int writeScoreFile(SCORE scores[],FILE *scoreFile){
    scoreFile = fopen("scores.txt","w+");
    if(scoreFile == NULL){
        logSDLError("Impossible d'ouvrir le fichier score pour l'écriture.");
        return(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; ++i) {
        if(fwrite(&scores[i],sizeof(SCORE),1,scoreFile) == 0){
            logSDLError("Impossible d'écrire sur le fichier score ouvert");
            return (EXIT_FAILURE);
        }
    }
    if(fclose(scoreFile)!=EXIT_SUCCESS){
        logSDLError("Impossible de fermer le fichier après écriture");
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}
SCORE createScore (PLAYER *player){
    SCORE score;
    score.position = 0;
    strcpy(score.name,player->name);
    score.score = player->score;
    return score;
}
void insertScore(SCORE scores[10],SCORE score){
    int j = 0;
    //On itère dans le tableau des scores
    for (int i = 0; i < 10; ++i) {
        //On touve à quel index on doit insérer le score.
        if(score.score>scores[i].score){
            j = i;
            break;
        }
    }
    //On déplace les scores inferieurs au score du joueur
    for(int i = 9; i>j;--i){
        strcpy(scores[i].name,scores[i-1].name);
        scores[i].score = scores[i-1].score;
        scores[i].position = i+1;
    }
    //On insère le score du joueur
    strcpy(scores[j].name,score.name);
    scores[j].score=score.score;
    scores[j].position = j+1;
}
void initScoreforTests(SCORE scores[10]){
    for (int i = 0; i < 10; ++i) {
        scores[i].position = i+1;
        scores[i].score = 1000/(i+1);
        strcpy(scores[i].name,"toto");
    }
}

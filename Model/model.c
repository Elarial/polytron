#include "model.h"
#include <stdio.h>
#include "../Controller/tools.h"
#include "../Vues/gameArea.h"
void displayGrid(GRID *grid){
    //Affichage de la grille
    for (int i = 0; i < grid->height; ++i) {
        for (int j = 0; j < grid->width; ++j) {
            printf("%d",grid->gridArray[i][j]);
        }
        printf("\n");

    }
}
GRID initGrid(int height,int width){
    GRID grid={height,width,NULL};
    int **data;
    data = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; ++i) {
        data[i] = malloc(width * sizeof(int));
    }
    grid.gridArray = data;
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0;  j< grid.width; j++) {
            grid.gridArray[i][j]= isEmpty;
        }
    }
    return grid;
}
int updateModel(MODEL *model, SDL_Renderer *renderer){

    for (int p = 0; p < model->nbPlayers; ++p) {
        if(model->players[p].id == player1){
            model->grid.gridArray[model->players[p].posX][model->players[p].posY] = p1Blocked;
        }else if(model->players[p].id == player2){
            model->grid.gridArray[model->players[p].posX][model->players[p].posY] = p2Blocked;
        }else{
            logSDLError("Impossible d'attribuer une valeur à la grille");
            return(EXIT_FAILURE);
        }
        partialUpdateGridView(model,renderer);
        switch (model->players[p].direction) {
        case up:
            model->players[p].posY--;
            break;
        case down:
            model->players[p].posY++;
            break;
        case left:
            model->players[p].posX--;
            break;
        case right:
            model->players[p].posX++;
            break;
        default:
            logSDLError("Direction de joueur non reconnue");
            return (EXIT_FAILURE);
            break;
        }

        model->players[p].score += 1;
    }
    return(EXIT_SUCCESS);
}
//TODO : check draw gamu.
int checkCollisions(MODEL *model){
    for (int p = 0; p < model->nbPlayers; ++p) {
        if(model->players[p].id == player1 && model->grid.gridArray[model->players[p].posX][model->players[p].posY] != isEmpty){
            printf("%d",model->grid.gridArray[model->players[p].posX][model->players[p].posY]);
            puts("player2");
            printf("SCORE P1 : %d\n",model->players[0].score);
            printf("SCORE P2 : %d\n",model->players[1].score);
            return player2;
        }
        else if(model->players[p].id == player2 && model->grid.gridArray[model->players[p].posX][model->players[p].posY] != isEmpty){
            puts("player1");
            printf("SCORE P1 : %d\n",model->players[0].score);
            printf("SCORE P2 : %d\n",model->players[1].score);
            return player1;
        }
    }
    return -1;
}

int updateDirection(MODEL *model, SDL_Keycode input){
    for (int p = 0; p < model->nbPlayers; ++p) {
        if(input == model->players[p].keyUp && model->players[p].direction != down){
            model->players[p].direction = up;
            return(EXIT_SUCCESS);
        }
        else if(input == model->players[p].keyLeft && model->players[p].direction != right){
            model->players[p].direction = left;
            return(EXIT_SUCCESS);
        }
        else if(input == model->players[p].keyDown && model->players[p].direction != up){
            model->players[p].direction = down;
            return(EXIT_SUCCESS);
        }
        else if(input == model->players[p].keyRight && model->players[p].direction != left){
            model->players[p].direction = right;
            return(EXIT_SUCCESS);
        }
    }
    return(EXIT_FAILURE);
}

void freeGridArray(GRID grid){
    if(&(grid.gridArray) != NULL){
        for (int i = 0; i < grid.height; ++i){
            free(grid.gridArray[i]);
        }
        free(grid.gridArray);
    }
}
PLAYER initPlayer(int playerId){
    PLAYER player;
    //TODO faire au propre
    int p1InitposX = p1DefaultposX;
    int p1InitposY = p1DefaultposY;
    int p2InitposX = p2DefaultposX;
    int p2InitposY = p2DefaultposY;

    if(playerId == player1){
        player.id=player1;
        SDL_Color color={0,0,255,SDL_ALPHA_OPAQUE};
        player.score = 0;
        player.color = color;
        player.posX = p1InitposX;
        player.posY = p1InitposY;
        player.direction = right;
        player.name = "Sonic";
        player.keyUp = SDLK_UP;
        player.keyLeft = SDLK_LEFT;
        player.keyDown = SDLK_DOWN;
        player.keyRight = SDLK_RIGHT;
    }else if (playerId == player2){
        player.id=player2;
        SDL_Color color = {255,205,0,SDL_ALPHA_OPAQUE};
        player.score = 0;
        player.color = color;
        player.posX = p2InitposX;
        player.posY = p2InitposY;
        player.direction = left;
        player.name = "Tails";
        player.keyUp = SDLK_z;
        player.keyLeft = SDLK_q;
        player.keyDown = SDLK_s;
        player.keyRight = SDLK_d;
    }else{
        logSDLError("Erreur lors de l'initialisation du joueur : Id non reconnu");
    }
    return player;
}
//TODO : passez le contexte pour la taille de la grille
MODEL initModel(){
    GRID grid = initGrid(640,480);
    PLAYER p1 = initPlayer(player1);
    PLAYER p2 = initPlayer(player2);
    int nbPlayers = 2;
    MODEL model = {grid,{p1,p2},nbPlayers};
    return model;
}
void resetModel(MODEL *model){
    model->grid = initGrid(640,480);
    for (int p = 0; p < model->nbPlayers; ++p) {
        model->players[p].score=0;
        if(model->players[p].id==player1){
            model->players[p].posX = p1DefaultposX;
            model->players[p].posY = p1DefaultposY;
            model->players[p].direction = right;
        }else if(model->players[p].id==player2){
            model->players[p].posX = p2DefaultposX;
            model->players[p].posY = p2DefaultposY;
            model->players[p].direction =left;
        }

    }
}

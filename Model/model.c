#include "model.h"
#include <stdio.h>
#include "../Controller/tools.h"
void displayGrid(GRID *grid){
    for (int i = 0; i < grid->height; ++i) {
        for (int j = 0; j < grid->width; ++j) {
            printf("%d",grid->gridArray[i][j]);
        }
        printf("\n");

    }

}
GRID initGridArray(int height,int width){
    GRID grid={height,width,NULL};
    int **data;
    data = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; ++i) {
        data[i] = malloc(width * sizeof(int));
    }
    grid.gridArray = data;
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0;  j< grid.width; j++) {
            grid.gridArray[i][j]= p1Blocked;
        }
    }
    return grid;
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
    if(playerId == player1){
        player.id=player1;
        SDL_Color color={0,0,255,SDL_ALPHA_OPAQUE};
        player.color = color;
    }else if (playerId == player2){
        player.id=player2;
        SDL_Color color = {255,205,0,SDL_ALPHA_OPAQUE};
        player.color = color;
    }else{
        logSDLError("Erreur lors de l'initialisation du joueur : Id non reconnu");
    }
    return player;
}


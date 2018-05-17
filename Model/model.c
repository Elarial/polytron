#include "model.h"
#include "../Vues/gameArea.h"
#include <stdio.h>

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
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < 10; ++j) {
            grid.gridArray[i][j] = computerBlocked;
            grid.gridArray[i][width-j] = computerBlocked;
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < width; ++j) {
            grid.gridArray[i][j] = computerBlocked;
            grid.gridArray[height-i-1][j] = computerBlocked;
        }
    }
    return grid;
}
int updateModel(MODEL *model, SDL_Renderer *renderer){

    for (int p = 0; p < model->nbPlayers; ++p) {
        if(model->players[p].id == player1){

            switch (model->players[p].direction) {
            case up:
                for (int i = 0; i < model->players[p].rect.w; ++i) {
                    for (int j = 0; j < model->players[p].rect.h; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y + model->players[p].rect.h-j] = p1Blocked;
                    }
                }
                break;
            case down:
                for (int i = 0; i < model->players[p].rect.w; ++i) {
                    for (int j = 0; j < model->players[p].rect.h; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y+j] = p1Blocked;
                    }
                }
                break;
            case left:
                for (int i = 0; i < model->players[p].rect.h; ++i) {
                    for (int j = 0; j < model->players[p].rect.w; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+model->players[p].rect.w-j][model->players[p].rect.y+i] = p1Blocked;
                    }

                }
                break;
            case right:
                for (int i = 0; i < model->players[p].rect.h; ++i) {
                    for (int j = 0; j < model->players[p].rect.w; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+j][model->players[p].rect.y+i] = p1Blocked;
                    }
                }
                break;
            default:
                break;
            }
        }else if(model->players[p].id == player2){
            switch (model->players[p].direction) {
            case up:
                for (int i = 0; i < model->players[p].rect.w; ++i) {
                    for (int j = 0; j < model->players[p].rect.h; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y + model->players[p].rect.h-j] = p2Blocked;
                    }
                }
                break;
            case down:
                for (int i = 0; i < model->players[p].rect.w; ++i) {
                    for (int j = 0; j < model->players[p].rect.h; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y+j] = p2Blocked;
                    }
                }
                break;
            case left:
                for (int i = 0; i < model->players[p].rect.h; ++i) {
                    for (int j = 0; j < model->players[p].rect.w; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+model->players[p].rect.w-j][model->players[p].rect.y+i] = p2Blocked;
                    }
                }
                break;
            case right:
                for (int i = 0; i < model->players[p].rect.h; ++i) {
                    for (int j = 0; j < model->players[p].rect.w; ++j) {
                        model->grid.gridArray[model->players[p].rect.x+j][model->players[p].rect.y+i] = p2Blocked;
                    }
                }
                break;
            default:
                break;
            }
        }else{
            logSDLError("Impossible d'attribuer une valeur à la grille");
            return(EXIT_FAILURE);
        }

        partialUpdateGridView(model,renderer);
        switch (model->players[p].direction) {
        case up:
            model->players[p].rect.y--;
            break;
        case down:
            model->players[p].rect.y++;
            break;
        case left:
            model->players[p].rect.x--;
            break;
        case right:
            model->players[p].rect.x++;
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

int checkCollisions(MODEL *model){

    //calcul des projections des rectangles des joueurs :
    int leftP1 = model->players[player1].rect.x+1;
    int rightP1 = model->players[player1].rect.x + model->players[player1].rect.w+1;
    int topP1 = model->players[player1].rect.y+1;
    int bottomP1 = model->players[player1].rect.y + model->players[player1].rect.h+1;
    int leftP2 = model->players[player2].rect.x+1;
    int rightP2 = model->players[player2].rect.x + model->players[player1].rect.w+1;
    int topP2 = model->players[player2].rect.y+1;
    int bottomP2 = model->players[player2].rect.y + model->players[player1].rect.h+1;
    //Si les projections se croisent : match nul
    if(bottomP1 > topP2 && topP1 < bottomP2 && rightP1 > leftP2 && leftP1 < rightP2){
        return draw;
    }
    for (int p = 0; p < model->nbPlayers; ++p) {
        if(model->players[p].id==player1){
            switch (model->players[p].direction) {
            case up:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y-1] != isEmpty){
                        return player2;
                    }
                }
                break;
            case down:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y+model->players[p].rect.h] != isEmpty){
                        return player2;
                    }
                }
                break;
            case left:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x-1][model->players[p].rect.y+i] != isEmpty){
                        return player2;
                    }
                }
                break;
            case right:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x + model->players[p].rect.w][model->players[p].rect.y+i] != isEmpty){
                        return player2;
                    }
                }
                break;
            default:
                break;
            }
        }
        if(model->players[p].id==player2){
            switch (model->players[p].direction) {
            case up:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y-1] != isEmpty){
                        return player1;
                    }
                }
                break;
            case down:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x+i][model->players[p].rect.y+model->players[p].rect.h] != isEmpty){
                        return player1;
                    }
                }
                break;
            case left:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x-1][model->players[p].rect.y+i] != isEmpty){
                        return player1;
                    }
                }
                break;
            case right:
                for (int i = 0; i < model->players[p].rect.h-1; ++i) {
                    if(model->grid.gridArray[model->players[p].rect.x + model->players[p].rect.w][model->players[p].rect.y+i] != isEmpty){
                        return player1;
                    }
                }
                break;
            default:
                break;
            }
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
        }else if(input == SDLK_p){

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
    player.rect.w = 20;
    player.rect.h = 20;

    if(playerId == player1){
        player.id=player1;
        SDL_Color color={0,0,255,SDL_ALPHA_OPAQUE};
        player.score = 0;
        player.color = color;
        player.rect.x = p1DefaultposX;
        player.rect.y = p1DefaultposY;
        player.direction = right;
        strcpy(player.name,"Sonic");
        player.keyUp = SDLK_UP;
        player.keyLeft = SDLK_LEFT;
        player.keyDown = SDLK_DOWN;
        player.keyRight = SDLK_RIGHT;
    }else if (playerId == player2){
        player.id=player2;
        SDL_Color color = {255,205,0,SDL_ALPHA_OPAQUE};
        player.score = 0;
        player.color = color;
        player.rect.x = p2DefaultposX;
        player.rect.y = p2DefaultposY;
        player.direction = left;
        strcpy(player.name,"Tails");
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
            model->players[p].rect.x = p1DefaultposX;
            model->players[p].rect.y = p1DefaultposY;
            model->players[p].direction = right;
        }else if(model->players[p].id==player2){
            model->players[p].rect.x = p2DefaultposX;
            model->players[p].rect.y = p2DefaultposY;
            model->players[p].direction =left;
        }

    }
}

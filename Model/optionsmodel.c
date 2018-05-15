#include "optionsmodel.h"
#include "string.h"


void updateOptionsMenu(int *position,int *activeView,MODEL *model,SDL_Keycode input,int *speed,MENU_OPTIONS *menuOptions,SDL_Renderer *renderer,GAMEMUSIC *gameMusic){
    switch (input) {
    case SDLK_DOWN:
        Mix_PlayChannel(-1,gameMusic->menuCursor,0);
        *(position) = *position + 1;
        break;
    case SDLK_UP:
        Mix_PlayChannel(-1,gameMusic->menuCursor,0);
        *(position) = *position - 1;
        break;
    case SDLK_a:
        Mix_PlayChannel(-1,gameMusic->menuDecide,0);
        selectOptionsActions(position,activeView,speed,menuOptions,model,renderer);
    default:
        break;
    }
    if(*(position)<0){
        *(position)=2;
    }
    if(*(position)>2){
        *(position)=0;
    }
}

void selectOptionsActions(int *position,int *activeView,int *speed,MENU_OPTIONS *menuOptions,MODEL *model,SDL_Renderer *renderer){
    switch (*position) {
    case menuOptionsSpeed:
        updateSpeed(speed,menuOptions);
        break;
    case menuOptionsKey:
        for (int p = 0; p < model->nbPlayers; ++p) {
            updateKeys(&(model->players[p]),menuOptions,*position,renderer);
        }
        break;
    case menuOptionsReturn:
        *position = 0;
        *activeView = main_menu;
        break;
    default:
        break;
    }
}
void updateSpeed(int *speed,MENU_OPTIONS *menuOptions){
    switch (*speed) {
    case NORMAL:
        *speed=FAST;
        //TODO : un fonction update de la texture + rectangle
        menuOptions->speedSelectValue.text = "RAPIDE";
        break;
    case FAST:
        *speed=SUPA_FAST;
        menuOptions->speedSelectValue.text = "TRES RAPIDE";
        break;
    case SUPA_FAST:
        *speed=NORMAL;
        menuOptions->speedSelectValue.text = "NORMAL";
        break;
    default:
        return;
        break;
    }
}
void updateKeys(PLAYER *player,MENU_OPTIONS *menuOptions,int position,SDL_Renderer *renderer){
    int ctr = 0;
    SDL_Event event = {0};
    updateTextKeys(player,&(menuOptions->keySelection),ctr);
    while (SDL_WaitEvent(&event)||ctr != 4){
        SDL_RenderClear(renderer);
        renderOptionsMenu(menuOptions,position,renderer);
        renderkeySelection(menuOptions,renderer);
        SDL_RenderPresent(renderer);
        if(event.type == SDL_KEYDOWN){
            switch (ctr) {
            case up:
                player->keyUp=event.key.keysym.sym;
                ctr++;
                updateTextKeys(player,&(menuOptions->keySelection),ctr);
                break;
            case down:
                player->keyDown=event.key.keysym.sym;
                ctr++;
                updateTextKeys(player,&(menuOptions->keySelection),ctr);
                break;
            case left:
                player->keyLeft=event.key.keysym.sym;
                ctr++;
                updateTextKeys(player,&(menuOptions->keySelection),ctr);
                break;
            case right:
                player->keyRight=event.key.keysym.sym;
                ctr++;
                return;
                break;
            default:
                return;
                break;
            }
        }
        SDL_Delay(10);
    }
}
void updateTextKeys(PLAYER *player,TEXT *text,int ctr){
    switch (ctr) {
    case up:
    if(player->id == player1){
        text->text="SELECTIONNER LA TOUCHE HAUT DU JOUEUR 1";
    }else{
        text->text="SELECTIONNER LA TOUCHE HAUT DU JOUEUR 2";
    }
        break;
    case down:
        if(player->id == player1){
            text->text="SELECTIONNER LA TOUCHE BAS DU JOUEUR 1";
        }else{
            text->text="SELECTIONNER LA TOUCHE BAS DU JOUEUR 2";
        }
        break;
    case left:

        if(player->id == player1){
            text->text="SELECTIONNER LA TOUCHE GAUCHE DU JOUEUR 1";
        }else{
            text->text="SELECTIONNER LA TOUCHE GAUCHE DU JOUEUR 2";
        }
        break;
    case right:

        if(player->id == player1){
            text->text="SELECTIONNER LA TOUCHE DROITE DU JOUEUR 1";
        }else{
            text->text="SELECTIONNER LA TOUCHE DROITE DU JOUEUR 2";
        }
        break;
    default:
        break;
    }
}

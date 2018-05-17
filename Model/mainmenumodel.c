#include <SDL2/SDL.h>
#include "mainmenumodel.h"
#include "../Controller/controller.h"

int updateMainMenu(int *position,SDL_Keycode input,GAMEMUSIC *gameMusic){
    switch (input) {
    case SDLK_DOWN:
        Mix_PlayChannel(-1,gameMusic->menuCursor,0);
        *(position) = *position + 1;
        break;
    case SDLK_UP:
        Mix_PlayChannel(-1,gameMusic->menuCursor,0);
        *(position) = *position - 1;
        break;
    case SDLK_RETURN:
        Mix_PlayChannel(-1,gameMusic->menuDecide,0);        
        return *(position);
    default:
        break;
    }
    if(*(position)<mainMenuSolo){
        *(position)=mainMenuScores;
    }
    if(*(position)>mainMenuScores){
        *(position)=mainMenuSolo;
    }
    return main_menu;
}

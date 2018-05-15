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
    case SDLK_a:
        Mix_PlayChannel(-1,gameMusic->menuDecide,0);
        if(*(position) == solo||*(position) ==VS){
            Mix_HaltMusic();
            Mix_PlayMusic(gameMusic->inGameMusic,-1);
        }
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

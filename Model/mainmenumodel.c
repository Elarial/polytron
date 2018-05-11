#include <SDL2/SDL.h>
#include "mainmenumodel.h"
#include "../Controller/controller.h"

int updateMainMenu(int *position,SDL_Keycode input){
    switch (input) {
    case SDLK_DOWN:
        *(position) = *position + 1;
        break;
    case SDLK_UP:
        *(position) = *position - 1;
        break;
    case SDLK_a:
        return (*(position)+1);
    default:
        break;
    }
    if(*(position)<0){
        *(position)=4;
    }
    if(*(position)>4){
        *(position)=0;
    }
    return main_menu;
}

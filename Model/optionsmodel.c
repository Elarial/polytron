#include <SDL2/SDL.h>
#include "optionsmodel.h"
#include "../Controller/controller.h"

int updateOptionsMenu(int *position,SDL_Keycode input){
    switch (input) {
    case SDLK_DOWN:
        *(position) = *position + 1;
        break;
    case SDLK_UP:
        *(position) = *position - 1;
        break;
    case SDLK_a:
        return *(position);
    default:
        break;
    }
    if(*(position)<0){
        *(position)=2;
    }
    if(*(position)>2){
        *(position)=0;
    }
    return *(position);
}


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "Controller/controller.h"

int main(void)
{

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDLcontext context = {&window,&renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT};


    if(initializeController(&context) != EXIT_SUCCESS || runListeners(&context) != EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }    
    return(EXIT_SUCCESS);
}


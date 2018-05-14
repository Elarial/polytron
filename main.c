#include <stdio.h>
#include <stdlib.h>
#include "Controller/controller.h"

int main(void)
{
    //Définition du contexte
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDLcontext context = {&window,&renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    //Initialisation du module controller et démarrage des écouteurs
    if(initializeController(&context) != EXIT_SUCCESS || runListeners(&context) != EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }    
    return(EXIT_SUCCESS);
}


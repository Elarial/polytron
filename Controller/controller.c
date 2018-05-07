#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "tools.h"
#include "controller.h"
#include "../Vues/mainMenu.h"
#include "../Vues/gameArea.h"
#include "../Model/model.h"


int initializeController(SDLcontext *context){
    if(initializeSDLcontexte(context->window,context->renderer,context->posX,context->posY,context->width,context->height)!= EXIT_SUCCESS
            ||initializeSDLttf()!= EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

int initializeSDLcontexte(SDL_Window **window, SDL_Renderer **renderer,int posX,int posY,int width,int height){
    if(SDL_Init(SDL_INIT_VIDEO) != EXIT_SUCCESS){
        logSDLError("Erreur lors de l'initialisation de SDL");
        return(EXIT_FAILURE);
    }
    *window=SDL_CreateWindow("polySanic",posX,posY,width,height,SDL_WINDOW_SHOWN);
    if(*window == NULL){
        logSDLError("Erreur lors de la creation de la fenetre");
        SDL_Quit();
        return(EXIT_FAILURE);
    }
    *renderer=SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(*renderer == NULL){
        logSDLError("Erreur lors de la creation du rendu");
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}
int initializeSDLttf(){
    if(TTF_Init()!= EXIT_SUCCESS){
        logSDLError("Erreur lors de l'initialisation du module TFF");
        SDL_Quit();
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}
int runListeners(SDLcontext *context){
    int end = 0;
    int ctr = 0;
    int activeView = 0;
    SDL_Event event = {0};
    MAINMENU mainMenu = initMainMenu(context);
    while(end == 0){
        while (SDL_PollEvent(&event)){
            //If user closes the window
            if (event.type == SDL_QUIT){
                end = 1;
            }
            //Mettre à jour le clip en fonction de l'input
            if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    ctr--;
                    break;
                case SDLK_LEFT:
                    break;
                case SDLK_DOWN:
                    ctr++;
                    break;
                case SDLK_RIGHT:
                    break;
                case SDLK_a:
                    activeView = ctr + 1;
                    break;
                case SDLK_ESCAPE:
                    end=1;
                    break;
                default:
                    break;
                }
            }
            if(ctr<0){
                ctr=4;
            }
            if(ctr>4){
                ctr=0;
            }
        }
        //Mise à jour de la vue.
        SDL_RenderClear(*(context->renderer));
        switch (activeView) {
        case 0:
            renderMainMenu(&mainMenu,ctr,*(context->renderer));
            break;
        case 1:
            logSDLError("Not implemented");
            activeView = 0;
            break;
        case 2:
            logSDLError("Not implemented");
            activeView = 0;
            break;
        case 3:
            logSDLError("Not implemented");
            activeView = 0;
            break;
        case 4:
            logSDLError("Not implemented");
            activeView = 0;
            break;
        case 5:
            logSDLError("Not implemented");
            activeView = 0;
            break;
        default:
            break;
        }
        SDL_RenderPresent(*(context->renderer));
    }
    SDL_DestroyWindow(*(context->window));
    SDL_DestroyRenderer(*(context->renderer));
    SDL_Quit();

    return EXIT_SUCCESS;
}

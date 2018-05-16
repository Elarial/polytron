#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "controller.h"
#include "../Vues/mainMenu.h"
#include "../Vues/gameArea.h"
#include "../Vues/options.h"
#include "../Vues/scores.h"
#include "../Model/model.h"
#include "../Model/mainmenumodel.h"
#include "../Model/optionsmodel.h"
#include "../Model/scoresmodel.h"


int initializeController(SDLcontext *context){
    if(initializeSDLcontexte(context->window,context->renderer,context->posX,context->posY,context->width,context->height)!= EXIT_SUCCESS
            ||initializeSDLttf()!= EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

int initializeSDLcontexte(SDL_Window **window, SDL_Renderer **renderer,int posX,int posY,int width,int height){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != EXIT_SUCCESS){
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
    int ctrMainMenu = mainMenuSolo;
    int ctrOptionsMenu = 0;
    int activeView = main_menu;
    int speed = NORMAL;
    int oneTimeAccess = 0;
    SDL_Event event = {0};
    MAINMENU mainMenu = initMainMenu(context);
    MENU_OPTIONS optionsMenu = initMenuOptions(context);
    MODEL model = initModel();
    SCORE scores[10]={0};
    FILE scoreFile;
    readScoreFile(scores,&scoreFile);
    SCORES_DISPLAY scoresMenu = initScoresDisplay(context,scores);
    GAMEMUSIC gameMusic = initGameMusic();
    GAMEAREA gameArea = initGameArea(context);

    //Mix_PlayMusic(gameMusic.mainMenuMusic,-1);
    while(end == 0){
        while (SDL_PollEvent(&event)){
            //If user closes the window
            if (event.type == SDL_QUIT){
                end = 1;
            }
            //Mettre à jour le jeu en fonction de l'input
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    end = 1;
                }
                switch (activeView) {
                case main_menu:
                    activeView = updateMainMenu(&ctrMainMenu,event.key.keysym.sym,&gameMusic);
                    renderMainMenu(&mainMenu,ctrMainMenu,*(context->renderer));
                    SDL_RenderPresent(*(context->renderer));
                    SDL_RenderClear(*(context->renderer));
                    break;
                case solo:
                    updateDirection(&model,event.key.keysym.sym);

                    break;
                case VS:
                    updateDirection(&model,event.key.keysym.sym);
                    break;
                case options:
                    updateOptionsMenu(&ctrOptionsMenu,&activeView,&model,event.key.keysym.sym,&speed,&optionsMenu,*(context->renderer),&gameMusic);
                    renderOptionsMenu(&optionsMenu,ctrOptionsMenu,*(context->renderer));
                    SDL_RenderPresent(*(context->renderer));
                    SDL_RenderClear(*(context->renderer));
                    break;
                case scores_menu:
                    updateScoresMenu(&activeView,event.key.keysym.sym,&gameMusic);
                    break;
                default:
                    break;
                }
            }
        }
        //Boucle d'itération du jeu

        switch (activeView) {
        case main_menu:
            renderMainMenu(&mainMenu,ctrMainMenu,*(context->renderer));
            SDL_Delay(10);
            break;
        case solo:
            while(oneTimeAccess != 1){
                model.nbPlayers=1;
                renderGameArea(&gameArea,*(context->renderer));
                oneTimeAccess = 1;
            }


            if(checkCollisions(&model) != -1){

                SDL_RenderClear(*context->renderer);
                //Mix_HaltMusic();
                SCORE newScore=createScore(&(model.players[player1]));
                insertScore(scores,newScore);
                writeScoreFile(scores,&scoreFile);
                updateScores(scores,&(scoresMenu),context);
                freeGridArray(model.grid);
                resetModel(&model);
                oneTimeAccess = 0;
                activeView = main_menu;
                //Mix_PlayMusic(gameMusic.mainMenuMusic,-1);
            }


            updateModel(&model,*(context->renderer));
            nextAnimationStep(&gameArea,&model,*context->renderer);

            SDL_RenderPresent(*(context->renderer));
            SDL_Delay(speed);
            break;
        case VS:
            while(oneTimeAccess != 1){
                 model.nbPlayers=2;
                renderGameArea(&gameArea,*(context->renderer));
                oneTimeAccess = 1;
            }


            if(checkCollisions(&model) != -1){
                //Mix_HaltMusic();
                SDL_RenderClear(*context->renderer);
                freeGridArray(model.grid);
                resetModel(&model);
                oneTimeAccess = 0;
                activeView = main_menu;
                //Mix_PlayMusic(gameMusic.mainMenuMusic,-1);
            }

            updateModel(&model,*(context->renderer));
            nextAnimationStep(&gameArea,&model,*context->renderer);

            SDL_RenderPresent(*(context->renderer));
            SDL_Delay(speed);
            break;
        case pVsAi:
            logSDLError("Not Implemented");
            activeView = main_menu;
            break;
        case options:
            renderOptionsMenu(&optionsMenu,ctrOptionsMenu,*(context->renderer));
            SDL_Delay(50);
            break;
        case scores_menu:
            renderScoresDisplay(scoresMenu,*(context->renderer));
            SDL_Delay(50);
            break;
        default:
            break;
        }
        SDL_RenderPresent(*(context->renderer));
    }
    //Détruire le renderer détruit également les textures associées.
    SDL_DestroyRenderer(*(context->renderer));
    SDL_DestroyWindow(*(context->window));
    freeGameMusic(&gameMusic);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

#ifndef MAINMENU_H
#define MAINMENU_H
#include <SDL2/SDL.h>
#include "../Controller/controller.h"
typedef struct {
    SDL_Texture *backgroundTexture;
    SDL_Texture *player1Texture;
    SDL_Rect    player1Rect;
    char*  player1Text;
    SDL_Texture *player2Texture;
    SDL_Rect    player2Rect;
    char* player2Text;
    SDL_Texture *playerVsAiTexture;
    SDL_Rect    playerVsAiRect;
    char* playerVsAiText;
    SDL_Texture *optionsTexture;
    SDL_Rect    optionsRect;
    char* optionsText;
    SDL_Texture *scoresTexture;
    SDL_Rect    scoresRect;
    char* scoresText;
    SDL_Color   defaultColor;
    SDL_Color   selectedColor;
    char* pathBackground;
    char* pathTTF;
    int fontSize;

}MAINMENU;

MAINMENU initMainMenu(SDLcontext *context);
int renderMainMenu(MAINMENU *mainMenu,int ctr,SDL_Renderer *renderer);
#endif // MAINMENU_H


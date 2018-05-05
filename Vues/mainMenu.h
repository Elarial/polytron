#ifndef MAINMENU_H
#define MAINMENU_H
#include <SDL2/SDL.h>
#include "../Controller/controller.h"
typedef struct {
    SDL_Texture *backgroundTexture;
    SDL_Texture *player1Texture;
    SDL_Rect    player1Rect;
    SDL_Texture *player2Texture;
    SDL_Rect    player2Rect;
    SDL_Texture *playerVsAiTexture;
    SDL_Rect    playerVsAiRect;
    SDL_Texture *optionsTexture;
    SDL_Rect    optionsRect;
    SDL_Texture *scoresTexture;
    SDL_Rect    scoresRect;
    SDL_Color   defaultColor;
    SDL_Color   selectedColor;
    int fontSize;

}MAINMENU;

MAINMENU initMainMenu(SDLcontext *context);
int renderMainMenu(MAINMENU *mainmenu,SDLcontext *context);
#endif // MAINMENU_H


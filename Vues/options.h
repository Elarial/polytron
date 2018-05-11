#ifndef OPTIONS_H
#define OPTIONS_H
#include <SDL2/SDL.h>
#include "../Controller/tools.h"
typedef struct{
    SDL_Texture *backgroundTexture;
    char *fontFile;
    SDL_Color defaultColor;
    SDL_Color selectedColor;
    TEXT optionsTitle;
    TEXT speedSelectTitle;
    TEXT speedSelectValue;
    TEXT keySelectTitle;
    TEXT keySelectValue;
    TEXT returnValue;
}MENU_OPTIONS;
typedef enum{
    menuOptionsSpeed,
    menuOptionsKey,
    menuOptionsReturn
}MENU_OPTIONS_POS;
typedef enum{
    NORMAL = 10,
    FAST = 5,
    SUPA_FAST = 2
}SPEED_VALUE;
MENU_OPTIONS initMenuOptions(SDLcontext *context);
int renderOptionsMenu(MENU_OPTIONS *menuOptions,int ctr,SDL_Renderer *renderer);
#endif // OPTIONS_H


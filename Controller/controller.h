#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
typedef struct {
    SDL_Window **window;
    SDL_Renderer **renderer;
    int posX;
    int posY;
    int width;
    int height;
}SDLcontext;
typedef enum{
    main_menu,
    solo,
    VS,

}ACTIVEVIEW;
int initializeController(SDLcontext *context);
int initializeSDLcontexte(SDL_Window **window, SDL_Renderer **renderer,int posX,int posY,int width,int height);
int initializeSDLttf();
int runListeners(SDLcontext *context);

#endif // CONTROLLER_H


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
    if(initializeController(&context) != 0){
        return(EXIT_FAILURE);
    }
    runListeners(&context);

   /*
    char* backgroundPath = "sonicpaper.bmp";
    int end = 0;
    int useClip = 0;

    SDL_Texture *textureBmp = NULL;
    SDL_Texture *background = NULL;
    SDL_Texture *spriteSheet = NULL;
    SDL_Event event = {0};
    //SDL_Rect clipRect = {0,0,100,100};
    //SDL_Rect srcRect = {0,0,0,0};
    SDL_Rect dstRect = {0,0,100,100};
    SDL_Rect spriteClips[4];
    SDL_Texture *texte = NULL;
    computeSpritesRects(spriteClips,4,100,100);

    initializeSDLcontexte(&window,&renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    initializeSDLttf();
    SDL_RenderClear(renderer);
    background = loadTextureImg(backgroundPath,renderer);
    spriteSheet = loadTextureImg("image.png",renderer);
    SDL_RenderClear(renderer);
    renderTexture(background,renderer,NULL,NULL);
    SDL_Color textColor = {0,0,255,100};
    texte = renderText("sega","NiseSega.TTF",textColor,20,renderer);
    */

}


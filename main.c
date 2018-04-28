#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
int renderTexture(SDL_Texture* texture,SDL_Renderer* renderer,SDL_Rect* srcRect, SDL_Rect* dstRect);
int initializeSDLcontexte(SDL_Window **window, SDL_Renderer **renderer,int posX,int posY,int width,int height);
int initializeRenderer(SDL_Window *window,SDL_Renderer **renderer);
SDL_Texture* loadTextureBmp(char* pathFile, SDL_Renderer* renderer);
SDL_Texture* loadTextureImg(char* pathFile, SDL_Renderer* renderer);

int main(void)
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    char* backgroundPath = "sonicpaper.bmp";
    int end = 0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *textureBmp = NULL;
    SDL_Texture *background = NULL;
    SDL_Texture *foreground = NULL;
    SDL_Event event = {0};
    SDL_Rect clipRect = {0,0,100,100};
    SDL_Rect dstRect = {0,0,0,0};

    initializeSDLcontexte(&window,&renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_RenderClear(renderer);
    background = loadTextureImg(backgroundPath,renderer);
    foreground = loadTextureImg("image.png",renderer);
    SDL_RenderClear(renderer);
    renderTexture(background,renderer,NULL,NULL);
    renderTexture(foreground,renderer,&clipRect,&dstRect);
     while(end == 0){
        while (SDL_PollEvent(&event)){
            //If user closes the window
            if (event.type == SDL_QUIT){
                end = 1;
            }
            /*//If user presses any key
            if (event.type == SDL_KEYDOWN){
                end = 1;
            }
            //If user clicks the mouse
            if (event.type == SDL_MOUSEBUTTONDOWN){
                end = 1;
            }*/
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(textureBmp);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}
void logSDLError(char* message){
    fprintf(stderr,"Erreur : %s\nErreur SDL : %s\n",message,SDL_GetError());
}
SDL_Texture* loadTextureImg(char* pathFile, SDL_Renderer* renderer){
    //On initialise le pointeur à NULL pour éviter les problèmes.
    SDL_Texture *texture = NULL;
    //On charge l'image
    texture = IMG_LoadTexture(renderer,pathFile);
    if(texture == NULL){
        logSDLError("Erreur lors du chargement de la texture.");
    }
    return texture;
}
SDL_Texture* loadTextureBmp(char* pathFile, SDL_Renderer* renderer){
    //On initialise le pointeur à NULL pour éviter les problèmes.
    SDL_Texture *texture = NULL;
    //On charge l'image
    SDL_Surface *loadedImage = SDL_LoadBMP(pathFile);
    //Si le chargement s'est bien passé, on convertit l'image en texture
    if (loadedImage != NULL){
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        //On vérifie que la convertion ce soit bien passée
        if (texture == NULL){
            logSDLError("Erreur lors de la creation de la texture");
        }
    }
    else {
        logSDLError("Erreur lors du chargement de l'image");
    }
    return texture;

}
int renderTexture(SDL_Texture* texture,SDL_Renderer* renderer,SDL_Rect* srcRect, SDL_Rect* dstRect){
    if(srcRect != NULL && dstRect != NULL){
        if (SDL_RectEmpty(srcRect) && SDL_RectEmpty(dstRect)){
            logSDLError("Rendu de texture impossible\nLes rectangles de source et de destination sont vides");
            return(EXIT_FAILURE);
        }
        if (SDL_RectEmpty(srcRect) && !SDL_RectEmpty(dstRect)){
            logSDLError("Rendu de texture impossible\nLe rectangle de source est vide");
            return(EXIT_FAILURE);
        }
        //Si le rectangle de source n'est pas vide et le rectangle de source est vide
        //La taille du rectangle de destination prend la taille du rectangle source
        if (!SDL_RectEmpty(srcRect) && SDL_RectEmpty(dstRect)){
            dstRect->w = srcRect->w;
            dstRect->h = srcRect->h;
        }
    }
    SDL_RenderCopy(renderer,texture,srcRect,dstRect);
    SDL_RenderPresent(renderer);
    return(EXIT_SUCCESS);
}
int initializeSDLcontexte(SDL_Window **window, SDL_Renderer **renderer,int posX,int posY,int width,int height){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
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

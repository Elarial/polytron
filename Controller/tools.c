#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "tools.h"

void logSDLError(char* message){
    fprintf(stderr,"Erreur : %s\nErreur SDL : %s\n",message,SDL_GetError());
}
TEXT initTexte(char* message,char* fontFile,SDL_Color textColor,int fontSize,SDL_Renderer *renderer){
    SDL_Texture *texture = NULL;
    texture = renderText(message,fontFile,textColor,fontSize,renderer);
    SDL_Rect textRect = createRectFromTexture(texture);
    TEXT text = {message,textRect,texture,textColor,fontSize};
    return text;
}

SDL_Texture* renderText(char* message,char* fontFile,SDL_Color color,int fontSize,SDL_Renderer *renderer){
    //On ouvre le fichier font
    TTF_Font *font = TTF_OpenFont(fontFile,fontSize);
    if(font==NULL){
        logSDLError("Erreur lors de la création de la font");
        return NULL;
    }
    SDL_Surface *surface = TTF_RenderText_Blended(font,message,color);
    if(surface == NULL){
        TTF_CloseFont(font);
        logSDLError("Erreur lors de la création de la surface à partir de la font");
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
    if(texture == NULL){
        logSDLError("Erreur lors de la création de la texture à partir de la suface font");
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;

}
int renderTexts (SDL_Texture* textures[], char* messages[],char* fontFile,SDL_Color color,int fontSize,SDL_Renderer *renderer,int nbElements){
    TTF_Font *font = TTF_OpenFont(fontFile,fontSize);
    if(font==NULL){
        logSDLError("Erreur lors de la création de la font");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < nbElements; ++i) {
        SDL_Surface *surface = TTF_RenderText_Blended(font,messages[i],color);
        if(surface == NULL){
            TTF_CloseFont(font);
            logSDLError("Erreur lors de la création de la surface à partir de la font");
            return EXIT_FAILURE;
        }
        textures[i] = SDL_CreateTextureFromSurface(renderer,surface);
        if(textures[i] == NULL){
            logSDLError("Erreur lors de la création de la texture à partir de la suface font");
            SDL_FreeSurface(surface);
            TTF_CloseFont(font);
            return(EXIT_SUCCESS);
        }
        SDL_FreeSurface(surface);
    }
    TTF_CloseFont(font);
    return(EXIT_SUCCESS);
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
    return(EXIT_SUCCESS);
}

void computeSpritesRects(SDL_Rect clips[],int nbClips,int clipWidth,int clipHeight){
    for(int i=0;i<nbClips;i++){
        clips[i].x=i/2*clipWidth;
        clips[i].y=i%2*clipHeight;
        clips[i].w=clipWidth;
        clips[i].h=clipHeight;
    }
}
SDL_Texture* loadTextureImg(char* pathFile, SDL_Renderer* renderer){
    //On initialise le pointeur à NULL pour éviter les problèmes.
    SDL_Texture *texture = NULL;
    //On charge l'image
    texture = IMG_LoadTexture(renderer,pathFile);
    if(texture == NULL){
        logSDLError("Erreur lors du chargement de la texture.");
        return NULL;
    }
    return texture;
}
SDL_Rect createRectFromTexture(SDL_Texture* texture){
    if(texture == NULL){
        logSDLError("Erreur lors de la création du rectangle");
        SDL_Rect rect = {0,0,0,0};
        return rect;
    }
    int iw,ih;    
    if(SDL_QueryTexture(texture,NULL,NULL,&iw,&ih)!=EXIT_SUCCESS){
        logSDLError("Erreur lors de l'execution de la requète à la texture.");
    }
    SDL_Rect rect={0,0,iw,ih};
    return rect;
}



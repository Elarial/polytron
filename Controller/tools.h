#ifndef TOOLS_H
#define TOOLS_H

#include <SDL2/SDL.h>
#include"controller.h"

SDL_Texture* loadTextureImg(char* pathFile, SDL_Renderer** renderer);
SDL_Texture* renderText(char* message,char* fontFile,SDL_Color color,int fontSize,SDL_Renderer **renderer);
SDL_Rect createRectFromTexture(SDL_Texture* texture);
int renderTexture(SDL_Texture* texture,SDL_Renderer** renderer,SDL_Rect* srcRect, SDL_Rect* dstRect);
void logSDLError(char* message);
void computeSpritesRects(SDL_Rect clips[],int nbClips,int clipWidth,int clipHeight);

#endif // TOOLS_H


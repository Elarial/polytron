#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdio.h>

int main(void)
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_EN_HEIGHT = 480;

    printf("Hello World!\n");
    SDL_Init(SDL_INIT_VIDEO);
    return 0;
}
void logSDLError(char* message){
    printf("%s\n",message);
    printf("%s\n",SDL_GetError());
}
SDL_Texture* loadTexture(char* pathFile, SDL_Renderer* renderer){

}
void renderTexture(SDL_Texture* texture,SDL_Renderer* renderer, SDL_Rect* Rectangle){

}
void createWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderer){

}
void initializeSDL(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        return(exit);
    }
}


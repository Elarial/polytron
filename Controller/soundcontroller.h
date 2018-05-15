#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H
#include <SDL2/SDL_mixer.h>
#include "tools.h"

typedef struct{
    Mix_Music *mainMenuMusic;
    Mix_Music *inGameMusic;
    Mix_Chunk *menuCursor;
    Mix_Chunk *menuDecide;

}GAMEMUSIC;
void freeGameMusic(GAMEMUSIC *gameMusic);
GAMEMUSIC initGameMusic();
#endif // SOUNDCONTROLLER_H


#include "soundcontroller.h"

GAMEMUSIC initGameMusic(){
    GAMEMUSIC gameMusic ={0};
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,1,1024)!=EXIT_SUCCESS){
        logSDLError("Erreur lors de l'ouverture du fichier audio");
    }
    gameMusic.mainMenuMusic = Mix_LoadMUS("menu.mp3");
    if(gameMusic.mainMenuMusic == NULL){
        logSDLError("Erreur lors du chargement de la musique du menu");
    }
    gameMusic.inGameMusic = Mix_LoadMUS("ingame.mp3");
    if(gameMusic.inGameMusic == NULL){
        logSDLError("Erreur lors du chargement de la musique du jeu");
    }
    gameMusic.menuCursor = Mix_LoadWAV("CURSOR.WAV");
    if(gameMusic.menuCursor == NULL){
        logSDLError("Erreur lors du chargement du son du curseur");
    }
    gameMusic.menuDecide=Mix_LoadWAV("DECIDE.WAV");
    if(gameMusic.menuDecide==NULL){
        logSDLError("Erreur lors du chargement du son de validation");
    }
    return gameMusic;
}
void freeGameMusic(GAMEMUSIC *gameMusic){
    if(gameMusic->mainMenuMusic != NULL){
        Mix_FreeMusic(gameMusic->mainMenuMusic);
    }
    if(gameMusic->inGameMusic != NULL){
        Mix_FreeMusic(gameMusic->inGameMusic);
    }
    if(gameMusic->menuCursor != NULL){
        Mix_FreeChunk(gameMusic->menuCursor);
    }
    if(gameMusic->menuDecide != NULL){
        Mix_FreeChunk(gameMusic->menuDecide);
    }
    Mix_Quit();
}


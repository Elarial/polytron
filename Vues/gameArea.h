#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <SDL2/SDL.h>
#include "../Controller/controller.h"
#include "../Model/model.h"

typedef struct{
    SDL_Texture *backgroundTexture;
    char *pathBackground;

}GAMEAREA;
///
/// \brief initGameArea Initialise la structure représentant le dessin de la zone de jeu
/// \param context SDLcontexte du jeu
/// \return La structure remplie.
///
GAMEAREA initGameArea(SDLcontext *context);
///
/// \brief setRenderDrawColorFromPlayer Règle la couleur du tracé en fonction du joueur
/// \param player Joueur concerné
/// \param renderer Rendu concerné par le tracé
/// \return
///
int setRenderDrawColorFromPlayer(PLAYER *player,SDL_Renderer *renderer);

int completeUpdateGridView(MODEL *model,SDL_Renderer *renderer);
int partialUpdateGridView(MODEL *model,SDL_Renderer *renderer);
#endif // GAMEAREA_H


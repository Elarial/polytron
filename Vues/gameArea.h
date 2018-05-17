#ifndef GAMEAREA_H
#define GAMEAREA_H
#include "../Controller/controller.h"
#include "../Model/model.h"
/**
  * \brief Le type utilisé pour représenter l'affichage de la zone de jeu
  */
typedef struct{
    char *spriteSheetName;
    int activeFrame;
    SDL_Texture *spritesTexture;
    SDL_Rect frames[4][3];

}ANIMATION;
typedef struct{
    SDL_Texture *loadingTexture; /**<Texture affiché en fond pour le chargement*/
    SDL_Texture *backgroundTexture; /**<Texture affiché en fond de la zone de jeu*/
    TTF_Font *font; /**<La font utilisées sur le rendu de la zone de jeu*/
    SDL_Color fontColor; /**<La couleur de la font utilisé sur le rendu de la zone de jeu */
    SDL_Rect fontRect; /**<Le rectangle dans lequel sera rendu la font. */
    ANIMATION animations[2]; /**<Animations des personnages */

}GAMEAREA;
void nextAnimationStep(GAMEAREA *gameArea,MODEL *model,SDL_Renderer *renderer);
void renderGameArea(GAMEAREA *gameArea,SDLcontext *context,MODEL *model);
ANIMATION initCharAnimation(char *spriteSheetName,SDL_Renderer *renderer,int height,int widths,int widthl);
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
/// \return EXIT_FAILURE si le réglage à échoué, EXIT_SUCCESS sinon.
///
int setRenderDrawColorFromPlayer(PLAYER *player,SDL_Renderer *renderer);
///
/// \brief completeUpdateGridView : Scan la totalité de la grille de jeu et trace les points concernés
/// \param model : Le modèle contenant la grille de jeu.
/// \param renderer : Le rendu sur lequel le tracé sera effectué.
/// \return EXIT_FAILURE si le tracé a échoué, EXIT_SUCCESS sinon.
///
int completeUpdateGridView(MODEL *model,SDL_Renderer *renderer);
///
/// \brief partialUpdateGridView : Met à jour la grille en fonction de la position des joueurs.
/// \param model : Modèle contenant la grille et les joueurs.
/// \param renderer : Rendu sur lequel sera tracé les points.
/// \return EXIT_FAILURE si le tracé a échoué, EXIT_SUCCESS sinon.
///
int partialUpdateGridView(MODEL *model,SDL_Renderer *renderer);
#endif // GAMEAREA_H


#ifndef MAINMENU_H
#define MAINMENU_H
#include <SDL2/SDL.h>
#include "../Controller/controller.h"
/**
  *\brief Type décrivant le menu principal.
  * \sa initMainMenu(SDLcontext *context).
  */
typedef struct {
    SDL_Texture *backgroundTexture; /**<Texture affiché en fond du menu principal. */
    SDL_Texture *player1Texture; /**<Texture affiché pour le mode 1 joueur. */
    SDL_Rect    player1Rect; /**<Rectangle de la texture player1Texture. */
    char*  player1Text; /**<Texte affiché pour le mode 1 joueur. */
    SDL_Texture *player2Texture; /**<Texture affiché pour le mode 2 joueurs */
    SDL_Rect    player2Rect; /**<Rectangle de la texture player2Texture. */
    char* player2Text; /**<Texte affiché pour le mode 2 joueurs. */
    SDL_Texture *playerVsAiTexture; /**<Texture affiché pour le mode joueur contre IA. */
    SDL_Rect    playerVsAiRect; /**<Rectange de la texture playerVsAiTexture. */
    char* playerVsAiText; /**<Texte affiché pour le mode joueur contre IA. */
    SDL_Texture *optionsTexture; /**<Texture affiché pour le mode options. */
    SDL_Rect    optionsRect; /**<Rectangle de la texture optionsTexture. */
    char* optionsText; /**<Texte affiché pour le mode options. */
    SDL_Texture *scoresTexture; /**<Texture affiché pour le mode scores. */
    SDL_Rect    scoresRect; /**<Rectangle de la texture scoresTexture. */
    char* scoresText; /**<Texte affiché pour le mode scores. */
    SDL_Color   defaultColor; /**<Couleur des textes par défaut. */
    SDL_Color   selectedColor; /**<Couleurs des textes lorsque'ils sont sélectionnés. */
    char* pathBackground; /**<Chemin de la texture de fond. */
    char* pathTTF; /**<Chemin du fichier TTF pour le rendu des textes. */
    int fontSize; /**<Taille des textes. */

}MAINMENU;
/**
  *\brief Enum représentant la position du curseur de sélection du menu principal.
  */
typedef enum{
    mainMenuSolo=0, /**<Curseur sur le menu SOLO */
    mainMenuPvp, /**<Curseur sur le menu joueur contre joueur */
    mainMenuPvAi, /*<Curseur sur le menu joueur contre IA */
    mainMenuOptions, /*Curseur sur le menu Options */
    mainMenuScores /*Curseur sur le menu Scores */
}MAINMENU_POS;
///
/// \brief initMainMenu : Permet d'initialiser le menu principal.
/// \param context : Contexte d'execution du programme.
/// \return La structure du menu principal.
///
MAINMENU initMainMenu(SDLcontext *context);
///
/// \brief renderMainMenu : Permet d'afficher le menu principal sur le rendu.
/// \param mainMenu : Le menu principal qui sera affiché.
/// \param ctr : Numéro du texte sélectionné.
/// \param renderer : Rendu sur lequel sera affiché le menu.
/// \return EXIT_FAILURE si le rendu du menu à échoué, EXIT_SUCCESS sinon.
///
int renderMainMenu(MAINMENU *mainMenu,int ctr,SDL_Renderer *renderer);
#endif // MAINMENU_H


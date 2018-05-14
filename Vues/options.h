#ifndef OPTIONS_H
#define OPTIONS_H
#include "../Controller/tools.h"
/**
  * \brief Structure représentant le menu options.
  * \sa initMenuOptions(SDLcontext *context);
  */
typedef struct{
    SDL_Texture *backgroundTexture; /**< Texture de fond du menu. */
    char *fontFile; /**< Fichier font utilisé pour le menu options. */
    SDL_Color defaultColor; /**< Couleur par défaut. */
    SDL_Color selectedColor; /**< Couleur lorsque le curseur est positionné sur le texte. */
    TEXT optionsTitle; /**< Le descriptif du titre du menu. */
    TEXT speedSelectTitle; /**< Le descriptif du titre de selection de la vitesse de jeu. */
    TEXT speedSelectValue; /**< Le descriptif de la valeur de selection de la vitesse de jeu. */
    TEXT keySelectTitle; /**< Le descriptif du titre de selection des touches du jeu. */
    TEXT keySelectValue; /**< Le descriptif de la valeur de selection des touches du jeu. */
    TEXT returnValue; /**< Le descriptif du texte permettant le retour au menu principal. */
    TEXT keySelection;/**<Le descriptif du texte informant la touche de saisie. */
}MENU_OPTIONS;
///
/// \brief initMenuOptions : Fonction d'initialisation du menu options.
/// \param context : Contexte d'exectution du programme
/// \return Le menu options initialisé
///
MENU_OPTIONS initMenuOptions(SDLcontext *context);
///
/// \brief renderOptionsMenu : Fonction permettant de copier le menu option sur le rendu en fonction de la position du curseur
/// \param menuOptions : Le menu options qui sera affiché
/// \param ctr : Le numéro de position du curseur de sélection
/// \param renderer : Le rendu sur lequel le menu option sera affiché
/// \return EXIT_FAILURE si un problème est survenu, EXIT_SUCCESS sinon.
///
int renderOptionsMenu(MENU_OPTIONS *menuOptions,int ctr,SDL_Renderer *renderer);
int renderkeySelection(MENU_OPTIONS *menuOptions,SDL_Renderer *renderer);
#endif // OPTIONS_H


#ifndef OPTIONSMODEL_H
#define OPTIONSMODEL_H
#include "../Vues/options.h"
#include "../Model/model.h"
#include "../Controller/controller.h"
/**
  * \brief Enum représentant la position du curseur de sélection du menu options.
  */

typedef enum{
    menuOptionsSpeed, /**< Curseur sur la sélection de vitesse de jeu */
    menuOptionsKey, /**< Curseur sur la sélection des touches */
    menuOptionsReturn /**< Curseur sur le retour au menu principal */
}MENU_OPTIONS_POS;
///
/// \brief updateOptionsMenu
/// \param position
/// \param input
/// \return
///
void updateOptionsMenu(int *position,int *activeView,MODEL *model,SDL_Keycode input,int *speed,MENU_OPTIONS *menuOptions,SDL_Renderer *renderer);
void selectOptionsActions(int *position,int *activeView,int *speed,MENU_OPTIONS *menuOptions,MODEL *model,SDL_Renderer *renderer);
void updateSpeed(int *speed,MENU_OPTIONS *menuOptions);
void updateKeys(PLAYER *player,MENU_OPTIONS *menuOptions,int position,SDL_Renderer *renderer);
void updateTextKeys(PLAYER *player,TEXT *text,int ctr);
#endif // OPTIONSMODEL_H


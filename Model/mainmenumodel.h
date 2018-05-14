#ifndef MAINMENUMODEL_H
#define MAINMENUMODEL_H
#include <SDL2/SDL.h>
///
/// \brief updateMainMenu : Fonction qui va permettre de mettre à jour l'affichage du menu principal.
/// \param position : Position du curseur sur le menu principal.
/// \param input : Touche appuyé par l'utilisateur.
/// \return
///
int updateMainMenu(int *position,SDL_Keycode input);
#endif // MAINMENUMODEL_H


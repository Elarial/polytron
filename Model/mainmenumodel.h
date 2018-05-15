#ifndef MAINMENUMODEL_H
#define MAINMENUMODEL_H
#include <SDL2/SDL.h>
#include "../Controller/soundcontroller.h"
#include "../Vues/mainMenu.h"
///
/// \brief updateMainMenu : Fonction qui va permettre de mettre à jour l'affichage du menu principal.
/// \param position : Position du curseur sur le menu principal.
/// \param input : Touche appuyé par l'utilisateur.
/// \return
///
int updateMainMenu(int *position,SDL_Keycode input,GAMEMUSIC *gameMusic);
#endif // MAINMENUMODEL_H


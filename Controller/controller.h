#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL2/SDL.h>
/**
 * \brief Le type utilisé pour représenter le contexte d'éxécution du programme.
 */
typedef struct {
    SDL_Window **window;        /**< Pointeur sur le pointeur de la fenètre dans lequel s'éxécutera le programme. */
    SDL_Renderer **renderer;        /**< Pointeur sur le pointeur du rendu associé à la fenètre. */
    int posX;       /**< Position de la fenètre sur l'axe des abscisses.*/
    int posY;       /**< Position de la fenètre sur l'axe des ordonnées.*/
    int width;      /**< Largeur de la fenètre en pixels.*/
    int height;     /**< Hauteur de la fenètre en pixels.*/
}SDLcontext;
/**
  * \brief Le menu actif.
  */
typedef enum{
    main_menu, /**<Menu principal */
    solo, /**<Mode 1 joueur */
    VS, /**<Mode 2 joueurs */
    pVsAi, /**<Mode 1 joueur contre IA */
    options, /**<Mode options */
    scores_menu /**<Mode scores */
}ACTIVEVIEW;
/**
  * \brief Enumération des vitesses de jeu possible (rafraichissement en ms)
  */
typedef enum{
    NORMAL = 10,
    FAST = 5,
    SUPA_FAST = 2
}SPEED_VALUE;
///
/// \brief initializeController : Initialise tous les modules nécéssaires au fonctionnement.
/// \param context : contexte d'exectution du programme.
/// \return EXIT_FAILURE si l'initialistion s'est mal passée, EXIT_SUCCESS sinon.
///
int initializeController(SDLcontext *context);
///
/// \brief initializeSDLcontexte : Permet d'initialiser le contexte d'execution du programme.
/// \param window : Double pointeur sur la fenetre du programme.
/// \param renderer : Double pointeur sur le Rendu associé à la fenetre.
/// \param posX : Position de la fenetre sur l'axe des abscisses de l'écran.
/// \param posY : Position de la fenetre sur l'axe des ordonnées de l'écran.
/// \param width : Largeur de la fenetre en pixels.
/// \param height : Hauteur de la fenetre en pixels.
/// \return EXIT_FAILURE si l'initialistion s'est mal passée, EXIT_SUCCESS sinon.
///
int initializeSDLcontexte(SDL_Window **window, SDL_Renderer **renderer,int posX,int posY,int width,int height);
///
/// \brief initializeSDLttf : Initialise la sous bibliothèque permettant de gérer les polices de caracètres.
/// \return EXIT_FAILURE si l'initialistion s'est mal passée, EXIT_SUCCESS sinon.
///
int initializeSDLttf();
///
/// \brief runListeners : Déclenche la boucle d'itération principale du programme et lance les écouteurs d'évennements.
/// \param context : Contexte d'éxécution du programme.
/// \return EXIT_FAILURE si l'initialistion s'est mal passée, EXIT_SUCCESS sinon.
///
int runListeners(SDLcontext *context);

#endif // CONTROLLER_H


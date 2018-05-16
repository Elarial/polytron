#ifndef MODEL_H
#define MODEL_H
#include <SDL2/SDL.h>
#define p1DefaultposX  (10)
#define p1DefaultposY (10)
#define p2DefaultposX (500)
#define p2DefaultposY (400)
/**
  *\brief Type représentant la grille de jeu.
  */
typedef struct{
    int height; /**< Hauteur de la grille de jeu */
    int width; /**< Largeur de la grille de jeu */
    int **gridArray; //* <Double pointeur représentant un tableau 2d */

}GRID;
/**
  *\brief Type représentant les caratctéristiques d'un joueur.
  */
typedef struct{
    int id; /**< Identifiant du joueur */
    char* name; /**< Nom du joueur */
    int score; /**< Score du joueur */
    int posX; /**< Position du joueur sur l'axe des abscisses de la grille */
    int posY; /**< Position du joueur sur l'axe des ordonnées de la grille */
    SDL_Rect rect; /**< Rectangle ou sera affiché le joueur */
    int direction; /**< Direction du curseur du joueur sur la grille */
    SDL_Keycode keyUp; /**< Touche réglé pour le joueur en tant que "HAUT" */
    SDL_Keycode keyDown;/**< Touche réglé pour le joueur en tant que "BAS" */
    SDL_Keycode keyLeft; /**< Touche réglé pour le joueur en tant que "GAUCHE" */
    SDL_Keycode keyRight; /**< Touche réglé pour le joueur en tant que "DROITE" */
    SDL_Color color; /**< Couleur de la trace laissée par le joueur */

}PLAYER;
/**
  *\brief Enum représenant les valeurs possibles dans la grille.
  */
typedef enum{
    isEmpty = 0, /**< Valeur prise par l'emplacement de la grille libre */
    computerBlocked, /**< Valeur prise par l'emplacement de la grille bloqué par le systeme */
    p1Blocked, /**< Valeur prise par l'emplacement de la grille bloqué par le joueur 1 */
    p2Blocked /**< Valeur prise par l'emplacement de la grille bloqué par le joueur 2 */
}GRIDSTATE;
/**
  *\brief Enum représentant les identifiants possibles pour les joueurs
  */
typedef enum{
    player1, /**< Valeur prise par l'id du joueur 1 */
    player2 /**< Valeur prise par l'id du joueur 2 */
}PLAYERID;
/**
  *\brief Enum représentant les directions possibles pour les joueurs.
  */
typedef enum{
    up, /**< Valeur prise par le direction "HAUT" */
    down, /**< Valeur prise par le direction BAS" */
    left, /**< Valeur prise par le direction "GAUCHE" */
    right /**< Valeur prise par le direction "DROITE" */
}DIRECTION;
/**
  *\brief Type représentant le modèle d'une partie.
  */
typedef struct{
    GRID grid;
    PLAYER players[2];
    int nbPlayers;
}MODEL;
void displayGrid(GRID *grid);
GRID initGrid(int height, int width);
void freeGridArray(GRID grid);
PLAYER initPlayer(int playerId);
MODEL initModel();
int updateModel(MODEL *model,SDL_Renderer *renderer);
int updateDirection(MODEL *model, SDL_Keycode input);
int checkCollisions(MODEL *model);
void resetModel(MODEL *model);
#endif // MODEL_H


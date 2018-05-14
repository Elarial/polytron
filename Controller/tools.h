#ifndef TOOLS_H
#define TOOLS_H
#include"controller.h"
/**
  * \brief Type représentant un texte qui sera affiché sur un rendu
  */
typedef struct{
    char* text; /** < chaine de caractères à afficher */
    SDL_Rect textRect; /**< Rectangle dans lequel sera affiché le rectangle */
    SDL_Texture *textTexture; /**< La texture qui sera affiché sur le rendu */
    SDL_Color textColor; /**< La couleur de la texture affiché */
    int fontSize; /**< La taille de la font qui sera affiché*/
    //TODO : remplacer fontSize par le type TTF_Font
}TEXT;
///
/// \brief initTexte : Initialise la structure TEXTE : Affiche un texte aux coordonnées 0;0 par défaut.
/// \param text : Le message qui sera affiché.
/// \param fontFile : Chemin du fichier contenant la font.
/// \param textColor : Couleur du texte.
/// \param fontSize : Taille de la font.
/// \return La structure TEXT initialisé.
///
TEXT initTexte(char* message,char* fontFile,SDL_Color textColor,int fontSize,SDL_Renderer *renderer);
///
/// \brief loadTextureImg : Génère une texture à partir d'une image.
/// \param pathFile : Chemin du fichier en relatif ou absolu.
/// \param renderer : Rendu dans lequel sera affiché la texture.
/// \return La texture généré
///
SDL_Texture* loadTextureImg(char* pathFile, SDL_Renderer* renderer);
///
/// \brief renderText : Génère une texture à partir d'un texte
/// \param message : Texte que sera affiché.
/// \param fontFile : Chemin du fichier contenant la font.
/// \param color : Couleur du texte qui sera affiché.
/// \param fontSize : Taille du texte qui sera affiché.
/// \param renderer : Rendu dans lequel sera affiché la texture.
/// \return La texture généré
///
SDL_Texture* renderText(char* message,char* fontFile,SDL_Color color,int fontSize,SDL_Renderer *renderer);
///
/// \brief renderTexts : Génère un tableau de texture à partir d'un tableau de texte.
/// \param textures : Le tableau de textures cible qui sera rempli.
/// \param messages : Le tableau de textes sources.
/// \param fontfile : Chemin du fichier contenant la font.
/// \param color : La couleur du texte qui sera affiché.
/// \param fontSize : La taille du texte qui sera affiché.SDL_Texture
/// \param renderer : Rendu dans lequel sera affiché la texture.
/// \param nbElements : Le nombre d'éléments qui sera généré.
///
int renderTexts (SDL_Texture* textures[], char messages[][30],char* fontfile,SDL_Color color,int fontSize,SDL_Renderer *renderer,int nbElements);
///
/// \brief createRectFromTexture : Créé un rectangle de la taille d'une texture.
/// \param texture : La texture dont la taille devra être mesuré.
/// \return Le rectangle généré.
///
SDL_Rect createRectFromTexture(SDL_Texture* texture);
///
/// \brief renderTexture : Copie une texture de la taille du rectangle source sur un rendu avec la taille du rectangle de destination.
/// \param texture : Texture à copier sur le rendu.
/// \param renderer : Rendu sur lequel la texture sera copié.
/// \param srcRect : Rectangle de la texture source.
/// \param dstRect : Rectangle de la texture de destination.
/// \return EXIT_FAILURE si la copie sur le rendu à échoué, EXIT_SUCCESS sinon.
///
int renderTexture(SDL_Texture* texture,SDL_Renderer* renderer,SDL_Rect* srcRect, SDL_Rect* dstRect);
///
/// \brief logSDLError : Log une erreur avec un message spécifique ainsi qu'une erreur système SDL.
/// \param message : Message spécifique qui sera enregistré.
///
void logSDLError(char* message);
///
/// \brief computeSpritesRects : Calcul un tableau de rectangles.
/// \param clips : Le tableau de rectangle qui sera calculé.
/// \param nbClips : Le nombre de rectangles à calculer.
/// \param clipWidth : La largeur des rectangles.
/// \param clipHeight : La hauteur des rectangles.
///
void computeSpritesRects(SDL_Rect clips[],int nbClips,int clipWidth,int clipHeight);

#endif // TOOLS_H


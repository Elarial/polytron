#include "options.h"
#include "../Model/optionsmodel.h"
#include "../Controller/tools.h"
MENU_OPTIONS initMenuOptions(SDLcontext *context){
    //Initialisation du menu options
    SDL_Texture *backgroundTexture = NULL;
    backgroundTexture = loadTextureImg("menubackground.png",*(context->renderer));
    char *fontFile ="NiseSega.TTF";
    SDL_Color defaultColor = {255,255,255,SDL_ALPHA_OPAQUE};
    SDL_Color selectedColor = {128,82,82,SDL_ALPHA_OPAQUE};
    int fontSize = 20;
    TTF_Font *font = getFontFromFile(fontFile,fontSize);
    //Initialisation des textes
    TEXT optionsTitle = initTexte("OPTIONS",font,defaultColor,*(context->renderer));
    TEXT speedSelectTitle = initTexte("VITESSE DU JEU",font,defaultColor,*(context->renderer));
    TEXT speedSelectValue = initTexte("NORMAL",font,defaultColor,*(context->renderer));
    TEXT keySelectTitle = initTexte("REGLAGE DES TOUCHES",font,defaultColor,*(context->renderer));
    TEXT keySelectValue = initTexte("COMMENCER LE REGLAGE",font,defaultColor,*(context->renderer));
    TEXT returnValue = initTexte("RETOUR AU MENU PRINCIPAL",font,defaultColor,*(context->renderer));
    TEXT keySelection = initTexte("SELECTIONNER LA TOUCHE HAUT DU JOUEUR 1",font,defaultColor,*(context->renderer));
    //Placement des textes
    optionsTitle.textRect.y=10,optionsTitle.textRect.x = context->width/2 - optionsTitle.textRect.w/2;
    speedSelectTitle.textRect.y = 100,speedSelectTitle.textRect.x = context->width/4 - speedSelectTitle.textRect.w/2 ;
    speedSelectValue.textRect.y = 100, speedSelectValue.textRect.x = context->width*3/4 - speedSelectTitle.textRect.w/2;
    keySelectTitle.textRect.y =200, keySelectTitle.textRect.x = context->width/4 - keySelectTitle.textRect.w/2 ;
    keySelectValue.textRect.y= 200, keySelectValue.textRect.x = context->width*3/4 - keySelectValue.textRect.w/2;
    returnValue.textRect.y=400,returnValue.textRect.x=context->width/2 - returnValue.textRect.w/2;
    keySelection.textRect.y=300,keySelection.textRect.x=context->width/2 - keySelection.textRect.w/2;
    MENU_OPTIONS menuOptions = {backgroundTexture,fontFile,font,defaultColor,selectedColor,optionsTitle,speedSelectTitle,speedSelectValue,keySelectTitle,keySelectValue,returnValue,keySelection};
    return menuOptions;

}
int renderkeySelection(MENU_OPTIONS *menuOptions,SDL_Renderer *renderer){
    menuOptions->keySelection.textTexture=renderText(menuOptions->keySelection.text,menuOptions->defaultColor,renderer,menuOptions->font);
    if(SDL_RenderCopy(renderer,menuOptions->keySelection.textTexture,NULL,&(menuOptions->keySelection.textRect))!=EXIT_SUCCESS){
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

int renderOptionsMenu(MENU_OPTIONS *menuOptions,int ctr,SDL_Renderer *renderer){
    if(ctr<0 || ctr>2){
        logSDLError("Index de position invalide");
        return(EXIT_FAILURE);
    }else{
        //Changement de la couleur du texte en fontion de l'input
        switch (ctr) {
        case menuOptionsSpeed:
            menuOptions->speedSelectValue.textTexture=renderText(menuOptions->speedSelectValue.text,menuOptions->selectedColor,renderer,menuOptions->font);
            menuOptions->keySelectValue.textTexture=renderText(menuOptions->keySelectValue.text,menuOptions->defaultColor,renderer,menuOptions->font);
            menuOptions->returnValue.textTexture=renderText(menuOptions->returnValue.text,menuOptions->defaultColor,renderer,menuOptions->font);
            break;
        case menuOptionsKey:
            menuOptions->keySelectValue.textTexture=renderText(menuOptions->keySelectValue.text,menuOptions->selectedColor,renderer,menuOptions->font);
            menuOptions->speedSelectValue.textTexture=renderText(menuOptions->speedSelectValue.text,menuOptions->defaultColor,renderer,menuOptions->font);
            menuOptions->returnValue.textTexture=renderText(menuOptions->returnValue.text,menuOptions->defaultColor,renderer,menuOptions->font);
            break;
        case menuOptionsReturn:
            menuOptions->returnValue.textTexture=renderText(menuOptions->returnValue.text,menuOptions->selectedColor,renderer,menuOptions->font);
            menuOptions->speedSelectValue.textTexture=renderText(menuOptions->speedSelectValue.text,menuOptions->defaultColor,renderer,menuOptions->font);
            menuOptions->keySelectValue.textTexture=renderText(menuOptions->keySelectValue.text,menuOptions->defaultColor,renderer,menuOptions->font);
        default:
            break;
        }
    }
    if(SDL_RenderCopy(renderer,menuOptions->backgroundTexture,NULL,NULL)!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du background sur le rendu");
        return(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer,menuOptions->optionsTitle.textTexture,NULL,&(menuOptions->optionsTitle.textRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du titre de selection de la vitesse sur le rendu");
        return(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer,menuOptions->speedSelectTitle.textTexture,NULL,&(menuOptions->speedSelectTitle.textRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du titre de selection de la vitesse sur le rendu");
        return(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer,menuOptions->speedSelectValue.textTexture,NULL,&(menuOptions->speedSelectValue.textRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie de la valeur de selection de la vitesse sur le rendu");
        return(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer,menuOptions->keySelectTitle.textTexture,NULL,&(menuOptions->keySelectTitle.textRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du titre de selection de la vitesse sur le rendu");
        return(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer,menuOptions->keySelectValue.textTexture,NULL,&(menuOptions->keySelectValue.textRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie de la valeur de selection de la vitesse sur le rendu");
        return(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer,menuOptions->returnValue.textTexture,NULL,&(menuOptions->returnValue.textRect))!=EXIT_SUCCESS){
        logSDLError("Echec lors de la copie du titre de selection de la vitesse sur le rendu");
        return(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

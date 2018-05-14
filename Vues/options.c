#include "options.h"
#include "../Model/optionsmodel.h"
#include "../Controller/tools.h"
MENU_OPTIONS initMenuOptions(SDLcontext *context){
    //Initialisation du menu options
    SDL_Texture *backgroundTexture = NULL;
    backgroundTexture = loadTextureImg("sonic_1_1991.jpg",*(context->renderer));
    char *fontFile ="NiseSega.TTF";
    SDL_Color defaultColor = {255,255,255,SDL_ALPHA_OPAQUE};
    SDL_Color selectedColor = {128,82,82,SDL_ALPHA_OPAQUE};
    int fontSize = 20;

    //Initialisation des textes
    TEXT optionsTitle = initTexte("OPTIONS",fontFile,defaultColor,fontSize,*(context->renderer));
    TEXT speedSelectTitle = initTexte("VITESSE",fontFile,defaultColor,fontSize,*(context->renderer));
    TEXT speedSelectValue = initTexte("NORMAL",fontFile,defaultColor,fontSize,*(context->renderer));
    TEXT keySelectTitle = initTexte("REGLAGE DES TOUCHES",fontFile,defaultColor,fontSize,*(context->renderer));
    TEXT keySelectValue = initTexte("COMMENCER LE REGLAGE",fontFile,defaultColor,fontSize,*(context->renderer));
    TEXT returnValue = initTexte("RETOUR AU MENU PRINCIPAL",fontFile,defaultColor,fontSize,*(context->renderer));
    TEXT keySelection = initTexte("SELECTIONNER LA TOUCHE HAUT DU JOUEUR 1",fontFile,defaultColor,fontSize,*(context->renderer));
    //Placement des textes
    optionsTitle.textRect.y=10,optionsTitle.textRect.x = 0;
    speedSelectTitle.textRect.y = 100,speedSelectTitle.textRect.x = 0;
    speedSelectValue.textRect.y = 100, speedSelectValue.textRect.x = 300;
    keySelectTitle.textRect.y =200, keySelectTitle.textRect.x = 0;
    keySelectValue.textRect.y= 200, keySelectValue.textRect.x = 300;
    returnValue.textRect.y=400,returnValue.textRect.x=context->width/2 - returnValue.textRect.w/2;
    keySelection.textRect.y=300,keySelection.textRect.x=context->width/2 - keySelection.textRect.w/2;
    MENU_OPTIONS menuOptions = {backgroundTexture,fontFile,defaultColor,selectedColor,optionsTitle,speedSelectTitle,speedSelectValue,keySelectTitle,keySelectValue,returnValue,keySelection};
    return menuOptions;

}
int renderkeySelection(MENU_OPTIONS *menuOptions,SDL_Renderer *renderer){
    menuOptions->keySelection.textTexture=renderText(menuOptions->keySelection.text,menuOptions->fontFile,menuOptions->defaultColor,menuOptions->keySelection.fontSize,renderer);
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
            menuOptions->speedSelectValue.textTexture=renderText(menuOptions->speedSelectValue.text,menuOptions->fontFile,menuOptions->selectedColor,menuOptions->speedSelectValue.fontSize,renderer);
            menuOptions->keySelectValue.textTexture=renderText(menuOptions->keySelectValue.text,menuOptions->fontFile,menuOptions->defaultColor,menuOptions->keySelectValue.fontSize,renderer);
            menuOptions->returnValue.textTexture=renderText(menuOptions->returnValue.text,menuOptions->fontFile,menuOptions->defaultColor,menuOptions->returnValue.fontSize,renderer);
            break;
        case menuOptionsKey:
            menuOptions->keySelectValue.textTexture=renderText(menuOptions->keySelectValue.text,menuOptions->fontFile,menuOptions->selectedColor,menuOptions->keySelectValue.fontSize,renderer);
            menuOptions->speedSelectValue.textTexture=renderText(menuOptions->speedSelectValue.text,menuOptions->fontFile,menuOptions->defaultColor,menuOptions->speedSelectValue.fontSize,renderer);
            menuOptions->returnValue.textTexture=renderText(menuOptions->returnValue.text,menuOptions->fontFile,menuOptions->defaultColor,menuOptions->returnValue.fontSize,renderer);
            break;
        case menuOptionsReturn:
            menuOptions->returnValue.textTexture=renderText(menuOptions->returnValue.text,menuOptions->fontFile,menuOptions->selectedColor,menuOptions->returnValue.fontSize,renderer);
            menuOptions->speedSelectValue.textTexture=renderText(menuOptions->speedSelectValue.text,menuOptions->fontFile,menuOptions->defaultColor,menuOptions->speedSelectValue.fontSize,renderer);
            menuOptions->keySelectValue.textTexture=renderText(menuOptions->keySelectValue.text,menuOptions->fontFile,menuOptions->defaultColor,menuOptions->keySelectValue.fontSize,renderer);
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

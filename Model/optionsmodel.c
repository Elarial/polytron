#include "optionsmodel.h"
#include "string.h"


void updateOptionsMenu(int *activeView,MODEL *model,SDL_Keycode input,int *speed,MENU_OPTIONS *menuOptions,SDL_Renderer *renderer,GAMEMUSIC *gameMusic){
    switch (input) {
    case SDLK_DOWN:
        Mix_PlayChannel(-1,gameMusic->menuCursor,0);
        menuOptions->position += 1;
        break;
    case SDLK_UP:
        Mix_PlayChannel(-1,gameMusic->menuCursor,0);
        menuOptions->position -= 1;
        break;
    case SDLK_RETURN:
        Mix_PlayChannel(-1,gameMusic->menuDecide,0);
        selectOptionsActions(activeView,speed,menuOptions,model,renderer);
    default:
        break;
    }
    if(menuOptions->position<0){
        menuOptions->position=4;
    }
    if(menuOptions->position>4){
        menuOptions->position=0;
    }
}

void selectOptionsActions(int *activeView,int *speed,MENU_OPTIONS *menuOptions,MODEL *model,SDL_Renderer *renderer){
    switch (menuOptions->position) {
    case menuOptionsSpeed:
        updateSpeed(speed,menuOptions);
        break;
    case menuOptionsP1Set:
        setPlayer(menuOptions,renderer,model,player1);
        break;
    case menuOptionsP2Set:
        setPlayer(menuOptions,renderer,model,player2);
        break;
    case menuOptionsKey:
        for (int p = 0; p < model->nbPlayers; ++p) {
            updateKeys(&(model->players[p]),menuOptions,renderer);
        }
        break;
    case menuOptionsReturn:
        menuOptions->position = 0;
        *activeView = main_menu;
        break;
    default:
        break;
    }
}
void setPlayer(MENU_OPTIONS *menuOptions, SDL_Renderer *renderer, MODEL *model,PLAYERID player){
    SDL_Event event={0};
    size_t maxSize = 20;
    char inputText[maxSize];
    inputText[0]='\0';
    int charCursor=0;
    SDL_bool eRenderText = SDL_FALSE;
    SDL_bool endInput = SDL_FALSE;
    SDL_StartTextInput();
    model->players[player].name[0] =' ',model->players[player].name[1] = '\0';
    SDL_RenderClear(renderer);
    renderOptionsMenu(menuOptions,renderer);
    SDL_RenderPresent(renderer);
    while (SDL_WaitEvent(&event)&&endInput==SDL_FALSE){
        if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_RETURN && strlen(inputText)>0){
                endInput = SDL_TRUE;
            }
            //Gestion du retour
            if(event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText)>0){
                charCursor --;
                inputText[charCursor] = '\0';
                eRenderText = SDL_TRUE;
            }
            //Gestion du copié
            if(event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL){
                SDL_SetClipboardText(inputText);
            }
            //Gestion du collé
            if(event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL){
                if((strlen(SDL_GetClipboardText()) + strlen(inputText))>maxSize){
                    logSDLError("La taille du buffer de copie est trop importante");
                }else{
                    strcat(inputText,SDL_GetClipboardText());
                    charCursor += strlen(SDL_GetClipboardText());
                    eRenderText = SDL_TRUE;
                }
            }
        }
        if(event.type == SDL_TEXTINPUT){
            //Si ce n'est pas un copé collé :
            if(((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL ) == 0){
                //Ajouter un caractère
                strcat(inputText,event.text.text);
                charCursor++;
                eRenderText = SDL_TRUE;

            }
        }
        //Faire le rendu du texte si nécéssaire
        if(eRenderText){
            SDL_RenderClear(renderer);
            renderOptionsMenu(menuOptions,renderer);
            if(strlen(inputText)!=0){
                switch (player) {
                case player1:
                    menuOptions->p1NameSetValue.textTexture = renderText(inputText,menuOptions->defaultColor,renderer,menuOptions->font);
                    SDL_QueryTexture(menuOptions->p1NameSetValue.textTexture,NULL,NULL,&(menuOptions->p1NameSetValue.textRect.w),&(menuOptions->p1NameSetValue.textRect.h));
                    SDL_RenderCopy(renderer,menuOptions->p1NameSetValue.textTexture,NULL,&(menuOptions->p1NameSetValue.textRect));
                    break;
                case player2:
                    menuOptions->p2NameSetValue.textTexture = renderText(inputText,menuOptions->defaultColor,renderer,menuOptions->font);
                    SDL_QueryTexture(menuOptions->p2NameSetValue.textTexture,NULL,NULL,&(menuOptions->p2NameSetValue.textRect.w),&(menuOptions->p2NameSetValue.textRect.h));
                    SDL_RenderCopy(renderer,menuOptions->p2NameSetValue.textTexture,NULL,&(menuOptions->p2NameSetValue.textRect));
                    break;
                default:
                    break;
                }

            }else{
                //afficher un espace puisqu'on ne peut pas faire le rendu d'un texte vide.
                menuOptions->p1NameSetValue.textTexture = renderText(" ",menuOptions->defaultColor,renderer,menuOptions->font);
                SDL_RenderCopy(renderer,menuOptions->p1NameSetValue.textTexture,NULL,&(menuOptions->p1NameSetValue.textRect));
            }
            SDL_RenderPresent(renderer);
        }
    }
    strcpy(model->players[player].name,inputText);
    SDL_StopTextInput();

}

void updateSpeed(int *speed,MENU_OPTIONS *menuOptions){
    switch (*speed) {
    case NORMAL:
        *speed=FAST;
        //TODO : un fonction update de la texture + rectangle
        menuOptions->speedSelectValue.text = "RAPIDE";
        break;
    case FAST:
        *speed=SUPA_FAST;
        menuOptions->speedSelectValue.text = "TRES RAPIDE";
        break;
    case SUPA_FAST:
        *speed=NORMAL;
        menuOptions->speedSelectValue.text = "NORMAL";
        break;
    default:
        return;
        break;
    }
}
void updateKeys(PLAYER *player,MENU_OPTIONS *menuOptions,SDL_Renderer *renderer){
    int ctr = 0;
    SDL_Event event = {0};
    updateTextKeys(player,&(menuOptions->keySelection),ctr);
    while (SDL_WaitEvent(&event)||ctr != 4){
        SDL_RenderClear(renderer);
        renderOptionsMenu(menuOptions,renderer);
        renderkeySelection(menuOptions,renderer);
        SDL_RenderPresent(renderer);
        if(event.type == SDL_KEYDOWN){
            switch (ctr) {
            case up:
                player->keyUp=event.key.keysym.sym;
                ctr++;
                updateTextKeys(player,&(menuOptions->keySelection),ctr);
                break;
            case down:
                player->keyDown=event.key.keysym.sym;
                ctr++;
                updateTextKeys(player,&(menuOptions->keySelection),ctr);
                break;
            case left:
                player->keyLeft=event.key.keysym.sym;
                ctr++;
                updateTextKeys(player,&(menuOptions->keySelection),ctr);
                break;
            case right:
                player->keyRight=event.key.keysym.sym;
                ctr++;
                return;
                break;
            default:
                return;
                break;
            }
        }
        SDL_Delay(10);
    }
}
void updateTextKeys(PLAYER *player,TEXT *text,int ctr){
    switch (ctr) {
    case up:
        if(player->id == player1){
            text->text="SELECTIONNER LA TOUCHE HAUT DU JOUEUR 1";
        }else{
            text->text="SELECTIONNER LA TOUCHE HAUT DU JOUEUR 2";
        }
        break;
    case down:
        if(player->id == player1){
            text->text="SELECTIONNER LA TOUCHE BAS DU JOUEUR 1";
        }else{
            text->text="SELECTIONNER LA TOUCHE BAS DU JOUEUR 2";
        }
        break;
    case left:

        if(player->id == player1){
            text->text="SELECTIONNER LA TOUCHE GAUCHE DU JOUEUR 1";
        }else{
            text->text="SELECTIONNER LA TOUCHE GAUCHE DU JOUEUR 2";
        }
        break;
    case right:

        if(player->id == player1){
            text->text="SELECTIONNER LA TOUCHE DROITE DU JOUEUR 1";
        }else{
            text->text="SELECTIONNER LA TOUCHE DROITE DU JOUEUR 2";
        }
        break;
    default:
        break;
    }
}

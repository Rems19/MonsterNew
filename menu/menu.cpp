#include "menu.h"

SDL_Surface* menuBackground_base;
SDL_Surface* menuBackground_play;
SDL_Surface* menuBackground_edit;
SDL_Surface* menuBackground_quit;

/****************** Nom de la fonction **********************
* initMenu                                                  *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* charge les surfaces du menu                               *
*********************** Entrées *****************************
* n'a pas d'entrées                                          *
*********************** Sorties *****************************
* ne retourne rien                                          *
************************************************************/
void initMenu() {
    menuBackground_base = loadImage("assets/menuetedit.bmp");
    menuBackground_play = loadImage("assets/menuetedit_play.bmp");
    menuBackground_edit = loadImage("assets/menuetedit_edit.bmp");
    menuBackground_quit = loadImage("assets/menuetedit_quit.bmp");
}

/****************** Nom de la fonction **********************
* isMouseOnPlayButton                                       *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de savoir si la souris est sur le bouton Play      *
* dans le menu                                              *
*********************** Entrées *****************************
* int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
*********************** Sorties *****************************
* revoie un booléen: true or false                          *
************************************************************/
bool isMouseOnPlayButton(int mouseX, int mouseY) {
    // Play button center : 148, 311   Radius : 53
    int dx = mouseX - 148, dy = mouseY - 311;
    return dx * dx + dy * dy <= 53 * 53;
}

/****************** Nom de la fonction **********************
* isMouseOnEditButton                                       *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de savoir si la souris est sur le bouton edtion    *
* dans le menu                                              *
*********************** Entrées *****************************
* int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
*********************** Sorties *****************************
* revoie un booléen: true or false                          *
************************************************************/
bool isMouseOnEditButton(int mouseX, int mouseY) {
    // Edit button center : 186, 226   Radius : 26
    int dx = mouseX - 186, dy = mouseY - 226;
    return dx * dx + dy * dy <= 26 * 26;
}

/****************** Nom de la fonction **********************
* isMouseOnQuitButton                                       *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de savoir si la souris est sur le bouton quitter   *
* dans le menu                                              *
*********************** Entrées *****************************
* int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
*********************** Sorties *****************************
* revoie un booléen: true or false                          *
************************************************************/
bool isMouseOnQuitButton(int mouseX, int mouseY) {
    // Quit button center : 220, 370   Radius : 26
    int dx = mouseX - 220, dy = mouseY - 370;
    return dx * dx + dy * dy <= 26 * 26;
}

/****************** Nom de la fonction **********************
* isMouseOnGameResetButton                                  *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de savoir si la souris est sur le bouton reset     *
* dans le jeu / editeur                                     *
*********************** Entrées *****************************
* int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
*********************** Sorties *****************************
* revoie un booléen: true or false                          *
************************************************************/
bool isMouseOnGameResetButton(int mouseX, int mouseY) {
    // Reset button center : 95, 530   Radius : 25
    int dx = mouseX - 95, dy = mouseY - 530;
    return dx * dx + dy * dy <= 26 * 26;
}

/****************** Nom de la fonction **********************
* getMenuBackground                                         *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de retourner l'image de fond du menu en fonction   *
* de la position de la souris (bouton plus gros quand on est*
* deçu)                                                     *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*à la fenêtre                                               *
*********************** Sorties *****************************
* SDL_Surface* menuBackground : surface selectionné         *
************************************************************/
SDL_Surface* getMenuBackground(int mouseX, int mouseY) {

    if (isMouseOnPlayButton(mouseX, mouseY)) {
        return menuBackground_play;
    }

    if (isMouseOnEditButton(mouseX, mouseY)) {
        return menuBackground_edit;
    }

    if (isMouseOnQuitButton(mouseX, mouseY)) {
        return menuBackground_quit;
    }

    return menuBackground_base;
}

/****************** Nom de la fonction **********************
* freeMenuSurfaces                                          *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Nettoie les surfaces chargées en mémoires du menu         *
*********************** Entrées *****************************
*il n'y a pas d'entrées                                     *
*********************** Sorties *****************************
* ne retourne rien                                          *
************************************************************/
void freeMenuSurfaces() {
    SDL_FreeSurface(menuBackground_base);
    SDL_FreeSurface(menuBackground_play);
    SDL_FreeSurface(menuBackground_edit);
    SDL_FreeSurface(menuBackground_quit);
}

#include "screen.h"
#include "affichage/surfaces.h"
#include <SDL/SDL_getenv.h>
#include <iostream>


/****************** Nom de la fonction **********************
* initScreen                                                *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet d'initialiser la fenetre à partir de constantes    *
* définies dans le .h en modifiant SDL_Surface* & screen    *
* passé en paramètre                                        *
*********************** Entrées *****************************
* SDL_Surface* & screen : correspont au fond de la fenêtre  *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void initScreen(SDL_Surface* & screen) {
    SDL_Surface *icone = SDL_LoadBMP("assets/icone.bmp");
    SDL_WM_SetIcon(icone, 0 );                                                //icone de l'appli
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE |SDL_DOUBLEBUF);   //création fenêtre

    SDL_WM_SetCaption("Monster", NULL);                                                                 //titre fenêtre
    SDL_FreeSurface(icone);
}

/****************** Nom de la fonction **********************
* setScreenBackground                                       *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet d'appliquer un fond d'écran en modifiant           *
* SDL_Surface* & screen à partir d'un SDL_Surface* passés   *
* en paramètre(on renomme)                                  *
*********************** Entrées *****************************
* SDL_Surface* & screen : correspont au fond de la fenêtre  *
*SDL_Surface* background: correspond à une image précedement*
* chargée                                                   *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void setScreenBackground(SDL_Surface* screen, SDL_Surface* background) {
    applySurface(0, 0, background, screen, NULL);
}

/****************** Nom de la fonction **********************
* updateScreen                                              *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet d'afficher SDL_Surface* & screen passée en         *
* en paramètre                                              *
*********************** Entrées *****************************
* SDL_Surface* & screen : correspont au fond de la fenêtre  *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void updateScreen(SDL_Surface* screen) {
    SDL_Flip(screen);
}

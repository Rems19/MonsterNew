#include "surfaces.h"

using namespace std;

SDL_Surface *surf_background;
SDL_Surface *surf_editorLevelChoice;
SDL_Surface *surf_haut;
SDL_Surface *surf_bas;
SDL_Surface *surf_gauche;
SDL_Surface *surf_droite;
SDL_Surface *surf_dormeur;
SDL_Surface *surf_glacon;
SDL_Surface *surf_glacon1;
SDL_Surface *surf_glacon2;
SDL_Surface *surf_monstre;
SDL_Surface *surf_livre;
SDL_Surface *surf_menu;
SDL_Surface *surf_win;
SDL_Surface *surf_winEnd;
SDL_Surface *surf_backgroundEditor;
SDL_Surface *surf_EditorHelp;
SDL_Surface *surf_Transparency;


struct ColorKey {
    int r, g, b;
};

/****************** Nom de la fonction **********************
* loadSurface                                               *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet de ne pas se préocuper du dossier contenant l'image*
* lorsque l'on utilise la fonction loadImage                *
*********************** Entrées *****************************
* string name : nom de la surface                           *
*********************** Sorties *****************************
* retourne la surface chargée                               *
************************************************************/
SDL_Surface* loadSurface(string name) {
    return loadImage("assets/" + name);
}

/****************** Nom de la fonction **********************
* loadSurface                                               *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet de ne pas se préocuper du dossier contenant l'image*
* lorsque l'on utilise la fonction loadImageWithColorKey    *
*********************** Entrées *****************************
* string name : nom de la surface                           *
* ColorKey ck : couleur rgb                                 *
* int alpha : opacité de la texture                         *
*********************** Sorties *****************************
* return la surface chargé                                  *
************************************************************/
SDL_Surface* loadSurface(string name, ColorKey ck, int alpha) {
    return loadImageWithColorKey("assets/" + name, ck.r, ck.g, ck.b, alpha);
}

/****************** Nom de la fonction **********************
* loadSurfaces()                                            *
******************** Auteur , Dates *************************
* REMI                      *
********************* Description ***************************
* Permet de charger l'ensemble des textures du programme    *
*********************** Entrées *****************************
*                                                           *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void loadSurfaces() {
    surf_background = loadSurface("background.bmp");
    surf_editorLevelChoice = loadSurface("niveaux.png");
    surf_haut = loadSurface("haut.png", {0, 255, 255},255);
    surf_bas = loadSurface("bas.png", {0, 255, 255},255);
    surf_gauche = loadSurface("gauche.png", {0, 255, 255},255);
    surf_droite = loadSurface("droite.png", {0, 255, 255},255);
    surf_dormeur = loadSurface("dormeur.png", {0, 255, 255},255);
    surf_glacon = loadSurface("glacon.png", {0, 255, 255},255);
    surf_glacon1 = loadSurface("glacon2.png", {0, 255, 255},255);
    surf_glacon2 = loadSurface("glacon3.png", {0, 255, 255},255);
    surf_monstre = loadSurface("monstre.png", {0, 255, 255},255);    
    surf_livre = loadSurface("livre.png", {0, 255, 255},255);
    surf_menu = loadSurface("menuetedit.bmp");
    surf_win = loadSurface("winSprite.bmp");
    surf_winEnd = loadSurface("winEndSprite.bmp");
    surf_backgroundEditor = loadSurface("background2.bmp");
    surf_EditorHelp = loadSurface("EditorHelp.bmp", {0, 255, 255},255);
    surf_Transparency = loadSurface("transparent.bmp", {0, 255, 255},190);
}

/****************** Nom de la fonction **********************
* freeSurfaces()                                            *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet de nettoyer l'ensemble des textures du programme en*
* en mémoire                                                *
*********************** Entrées *****************************
*                                                           *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void freeSurfaces() {
    SDL_FreeSurface(surf_background);
    SDL_FreeSurface(surf_editorLevelChoice);
    SDL_FreeSurface(surf_haut);
    SDL_FreeSurface(surf_bas);
    SDL_FreeSurface(surf_gauche);
    SDL_FreeSurface(surf_droite);
    SDL_FreeSurface(surf_dormeur);
    SDL_FreeSurface(surf_glacon);
    SDL_FreeSurface(surf_glacon1);
    SDL_FreeSurface(surf_glacon2);
    SDL_FreeSurface(surf_monstre);
    SDL_FreeSurface(surf_livre);
    SDL_FreeSurface(surf_menu);
    SDL_FreeSurface(surf_win);
    SDL_FreeSurface(surf_winEnd);
    SDL_FreeSurface(surf_EditorHelp);
    SDL_FreeSurface(surf_backgroundEditor);
    SDL_FreeSurface(surf_Transparency);    
}

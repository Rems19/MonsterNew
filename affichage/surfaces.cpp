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
SDL_Surface *surf_monstre;
SDL_Surface *surf_livre;
SDL_Surface *surf_menu;
SDL_Surface *surf_win;
SDL_Surface *surf_winEnd;

struct ColorKey {
    int r, g, b;
};

SDL_Surface* loadSurface(string name) {
    return loadImage("assets/" + name);
}

SDL_Surface* loadSurface(string name, ColorKey ck) {
    return loadImageWithColorKey("assets/" + name, ck.r, ck.g, ck.b);
}

void loadSurfaces() {
    surf_background = loadSurface("background.bmp");
    surf_editorLevelChoice = loadSurface("level.png");
    surf_haut = loadSurface("haut.png", {0, 255, 255});
    surf_bas = loadSurface("bas.png", {0, 255, 255});
    surf_gauche = loadSurface("gauche.png", {0, 255, 255});
    surf_droite = loadSurface("droite.png", {0, 255, 255});
    surf_dormeur = loadSurface("dormeur.png", {0, 255, 255});
    surf_glacon = loadSurface("glacon.png", {0, 255, 255});
    surf_monstre = loadSurface("monstre.png", {0, 255, 255});
    surf_livre = loadSurface("livre.png", {0, 255, 255});
    surf_menu = loadSurface("menuetedit.bmp");
    surf_win = loadSurface("winSprite.bmp");
    surf_winEnd = loadSurface("winEndSprite.bmp");
}

void freeSurfaces() {
    SDL_FreeSurface(surf_background);
    SDL_FreeSurface(surf_editorLevelChoice);
    SDL_FreeSurface(surf_haut);
    SDL_FreeSurface(surf_bas);
    SDL_FreeSurface(surf_gauche);
    SDL_FreeSurface(surf_droite);
    SDL_FreeSurface(surf_dormeur);
    SDL_FreeSurface(surf_glacon);
    SDL_FreeSurface(surf_monstre);
    SDL_FreeSurface(surf_livre);
    SDL_FreeSurface(surf_menu);
    SDL_FreeSurface(surf_win);
    SDL_FreeSurface(surf_winEnd);
}

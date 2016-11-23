#ifndef SURFACES_H
#define SURFACES_H

#include <SDL/SDL.h>
#include <SDL_Funcs.h>

extern SDL_Surface *surf_background;
extern SDL_Surface *surf_haut;
extern SDL_Surface *surf_bas;
extern SDL_Surface *surf_gauche;
extern SDL_Surface *surf_droite;
extern SDL_Surface *surf_dormeur;
extern SDL_Surface *surf_glacon;
extern SDL_Surface *surf_monstre;
extern SDL_Surface *surf_livre;
extern SDL_Surface *surf_menu;
extern SDL_Surface *surf_win;
extern SDL_Surface *surf_winEnd;

void loadSurfaces();
void freeSurfaces();

#endif // SURFACES_H

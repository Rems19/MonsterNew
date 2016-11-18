#ifndef MENU_H
#define MENU_H

#include "affichage/sdl_funcs.h"

void initMenu();
bool isMouseOnPlayButton(int mouseX, int mouseY);
bool isMouseOnEditButton(int mouseX, int mouseY);
bool isMouseOnQuitButton(int mouseX, int mouseY);
SDL_Surface* getMenuBackground(int mouseX, int mouseY);
void freeMenuSurfaces();

#endif // MENU_H

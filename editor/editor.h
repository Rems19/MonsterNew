#ifndef EDITOR_H
#define EDITOR_H

#include "affichage/sdl_funcs.h"
#include "game/grid.h"

void checkEditorKeyEvent(SDLKey key);
void checkEditorMouseClickEvent(Uint8 button, int coordX, int coordY);
void saveLevel(TGrid grid, int level);
void drawCursor(SDL_Surface *s, int mouseX, int mouseY);
bool levelSelect(TGrid & grid, int mouseX, int mouseY);

#endif // EDITOR_H

#ifndef EDITOR_H
#define EDITOR_H

#include "affichage/sdl_funcs.h"
#include "game/grid.h"

void checkEditorKeyEvent(CaseType & choice);
void checkEditorMouseClickEvent(TGrid &grid, int coordX, int coordY, CaseType choice);
void saveLevel(TGrid grid, int level);
void drawCursor(SDL_Surface *s, int mouseX, int mouseY, int choice);
int levelSelect(int mouseX, int mouseY);
SDL_Surface* getEditorForeBackground(int mouseX, int mouseY);

#endif // EDITOR_H

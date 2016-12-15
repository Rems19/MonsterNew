#ifndef EDITOR_H
#define EDITOR_H

#include "affichage/sdl_funcs.h"
#include "game/grid.h"

//evenement
void checkEditorKeyEvent(CaseType & choice);
void checkEditorMouseClickEvent(TGrid &grid, int coordX, int coordY, CaseType choice);

//select/save
void saveLevel(TGrid grid, int level);
int levelSelect(int mouseX, int mouseY);

//test
bool isMouseOnModeButton(int mouseX, int mouseY);
void setSelectCursor(int mouseX, int mouseY, CaseType &  choice);


//affichage
void setEditorForeground(SDL_Surface *screen, int mouseX, int mouseY, int modeEditor);
void setEditorBackground(SDL_Surface *screen, int modeEditor);
void drawCursor(SDL_Surface *s, int mouseX, int mouseY, int choice, int modeEditor);

#endif // EDITOR_H

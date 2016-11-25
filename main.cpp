#include <iostream>
#include "affichage/screen.h"
#include "menu/menu.h"
#include "game/grid.h"
#include "editor/editor.h"
#include "affichage/surfaces.h"

using namespace std;

int main() {

    bool quit = false;

    // States
    const int menu = 0, game = 1, editorMenu = 2, editorGrid = 3;
    int state = menu; // Starting state : menu

    // Current level for game state
    int currentLevel = 1;

    int levelEdit = 0;

    int maxLevel = 10;

    //  int choice = 1;
    int choice = 1;

    // Direction Initialisation
    Direction direction = NONE;
    // SDL initialization
    initSDL();

    // Screen initialization
    SDL_Surface* screen;
    initScreen(screen);

    // Surfaces initialization
    loadSurfaces();

    // Menu initialization
    initMenu();

    // Grid initialization
    TGrid grid;
    initGrid(grid);

    //Surfaces game Initialization
    loadSurfaces();

    SDL_Event event;
    int mouseX, mouseY; // Cursor coordinates in pixels
    int mouseXCoord, mouseYCoord; // Coordinates of the case pointed by the cursor

    while (!quit) {

        // Event management
        while (SDL_PollEvent(&event)) {

            switch (event.type) {

            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEMOTION:
                mouseX = event.button.x;
                mouseY = event.button.y;
                pixelsToCoords(mouseX, mouseY, mouseXCoord, mouseYCoord);
                break;

            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (state == menu) {
                        if (isMouseOnPlayButton(mouseX, mouseY))
                            state = game;
                        else if (isMouseOnEditButton(mouseX, mouseY))
                            state = editorMenu;
                        else if (isMouseOnQuitButton(mouseX, mouseY))
                            quit = true;
                    } else if (state == editorMenu) {
                        if(levelEdit != 0)
                            state = editorGrid;

                    } else if (state == game) {
                        if(((mouseX - 95) * (mouseX - 95) + (530 - mouseY) * (530 - mouseY)) <= 25 * 25) {
                            initGrid(grid);
                            loadLevel(grid, currentLevel);
                        }
                    }
                    break;
                default: break;
                }
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    if(state == menu) {
                        quit = true;
                    } else {
                        if (state = editorGrid)
                            saveLevel(grid, levelEdit);
                        state = menu;
                    }
                    break;
                default: break;
                }
                break;
            default: break;
            }

        }

        if (state == menu) {

            setScreenBackground(screen, getMenuBackground(mouseX, mouseY));
            currentLevel = 1;
            levelEdit = 0;
            initGrid(grid);
            loadLevel(grid, 1);

        } else if (state == game) {

            mouvement(grid, event, direction, screen, mouseXCoord, mouseYCoord, currentLevel);
            setScreenBackground(screen, surf_background);
            draw(grid, screen);
            levelWin(grid, screen, currentLevel, state, maxLevel);

        } else if (state == editorGrid) {                //si on a choisi le niveau on lance l'éditeur

            setScreenBackground(screen, surf_background);
            draw(grid, screen);
            drawCursor(screen, mouseX, mouseY, choice);
            checkEditorKeyEvent(choice);
            checkEditorMouseClickEvent(grid, mouseXCoord, mouseYCoord, choice);



        } else {
            setScreenBackground(screen, surf_editorLevelChoice);
            levelEdit = levelSelect(mouseX, mouseY);
            if(levelEdit != 0)
                loadLevel(grid, levelEdit);
        }

        updateScreen(screen);
    }

    SDL_FreeSurface(screen);
    freeMenuSurfaces();
    freeSurfaces();
}


#include "menu.h"

SDL_Surface* menuBackground_base;
SDL_Surface* menuBackground_play;
SDL_Surface* menuBackground_edit;
SDL_Surface* menuBackground_quit;

void initMenu() {
    menuBackground_base = loadImage("assets/menuetedit.bmp");
    menuBackground_play = loadImage("assets/menuetedit_play.bmp");
    menuBackground_edit = loadImage("assets/menuetedit_edit.bmp");
    menuBackground_quit = loadImage("assets/menuetedit_quit.bmp");
}

bool isMouseOnPlayButton(int mouseX, int mouseY) {
    // Play button center : 148, 311   Radius : 53
    int dx = mouseX - 148, dy = mouseY - 311;
    return dx * dx + dy * dy <= 53 * 53;
}

bool isMouseOnEditButton(int mouseX, int mouseY) {
    // Edit button center : 186, 226   Radius : 26
    int dx = mouseX - 186, dy = mouseY - 226;
    return dx * dx + dy * dy <= 26 * 26;
}

bool isMouseOnQuitButton(int mouseX, int mouseY) {
    // Quit button center : 220, 370   Radius : 26
    int dx = mouseX - 220, dy = mouseY - 370;
    return dx * dx + dy * dy <= 26 * 26;
}

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

void freeMenuSurfaces() {
    SDL_FreeSurface(menuBackground_base);
    SDL_FreeSurface(menuBackground_play);
    SDL_FreeSurface(menuBackground_edit);
    SDL_FreeSurface(menuBackground_quit);
}

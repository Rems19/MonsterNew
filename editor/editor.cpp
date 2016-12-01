#include "editor.h"

void checkEditorKeyEvent(CaseType & choice) {

    Uint8 *keystates = SDL_GetKeyState( NULL );

    if(keystates[SDLK_a]){
        choice = MONSTER;
    }
    if(keystates[SDLK_z]){
        choice = ICE;
    }
    if(keystates[SDLK_e]){
        choice = BOOK;
    }
    if(keystates[SDLK_r]){
        choice = SLEEPER;
    }
    if(keystates[SDLK_UP]){
        choice = UP_E;
    }
    if(keystates[SDLK_DOWN]){
        choice = DOWN_E;
    }
    if(keystates[SDLK_RIGHT]){
        choice = RIGHT_E;
    }
    if(keystates[SDLK_LEFT]){
        choice = LEFT_E;
    }
}

void checkEditorMouseClickEvent(TGrid & grid, int coordX, int coordY, CaseType choice) {

    Uint8 mousestates = SDL_GetMouseState(NULL,NULL);

    if (mousestates &SDL_BUTTON_LEFT) {

        grid[coordX][coordY].type = EMPTY;
        switch(choice) {
        case UP_E:
            grid[coordX][coordY].direction = UP;
            break;
        case DOWN_E:
            grid[coordX][coordY].direction = DOWN;
            break;
        case RIGHT_E:
            grid[coordX][coordY].direction = RIGHT;
            break;
        case LEFT_E:
            grid[coordX][coordY].direction = LEFT;
            break;
        default:
            grid[coordX][coordY].type = choice;
            grid[coordX][coordY].direction = NONE;
            break;
        }

    } else if(mousestates & SDL_BUTTON_RMASK) {
        grid[coordX][coordY].type = EMPTY;
        grid[coordX][coordY].direction = NONE;

    }
}

void drawCursor(SDL_Surface *s, int mouseX, int mouseY, int choice) {

    if((mouseX && mouseY) != 0) {
        switch (choice) {

        case MONSTER :
            applySurface(mouseX, mouseY, surf_monstre, s, NULL);
            break;
        case ICE:
            applySurface(mouseX, mouseY, surf_glacon, s, NULL);
            break;
        case BOOK:
            applySurface(mouseX, mouseY, surf_livre, s, NULL);
            break;
        case SLEEPER:
            applySurface(mouseX, mouseY, surf_dormeur, s, NULL);
            break;
        case UP_E:
            applySurface(mouseX, mouseY, surf_haut, s, NULL);
            break;
        case DOWN_E:
            applySurface(mouseX, mouseY, surf_bas, s, NULL);
            break;
        case RIGHT_E:
            applySurface(mouseX, mouseY, surf_droite, s, NULL);
            break;
        case LEFT_E:
            applySurface(mouseX, mouseY, surf_gauche, s, NULL);
            break;
        }
    }
}

int levelSelect(int mouseX, int mouseY) {
    int x = 0;
    int y = 0;
    int found = 0;
    while (x < 3 && y < 5 && found == 0) {
        int dx = mouseX - (62 + 90 * x), dy = mouseY - (160 + 80 * y);
        if (dx * dx + dy * dy <= 25 * 25) {
            found = 3 * y + x + 1;
        }
        x++;
        if (x == 3) {
            y++;
            x = 0;
        }
    }
    return found;
}

void saveLevel(TGrid grid, int level) {

    int type;

    std::string lvl;
    lvl = "levels/niveaux" + std::to_string(level) + ".txt";

    std::ofstream fichier(lvl,  std::ios::out |  std::ios::trunc);

    if(fichier) {
        for(int i = 0; i < WIDTH; i++) {
            for(int j = 0; j < HEIGHT; j++) {

                type = grid[i][j].type;

                if(type == EMPTY)
                     switch(grid[i][j].direction) {
                     case UP:
                         type = UP_E;
                         break;
                     case DOWN:
                         type = DOWN_E;
                         break;
                     case RIGHT:
                         type = RIGHT_E;
                         break;
                     case LEFT:
                         type = LEFT_E;
                         break;
                     default: break;
                     }
                fichier << type << std::endl;
            }
        }
        fichier.close();
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture." << std::endl;
    }
}

#include "editor.h"

void checkEditorKeyEvent(SDLKey key, int choice) {
    switch (key) {
    case SDLK_a:
        choice = 1;
        break;
    case SDLK_z:
        choice = 2;
        break;
    case SDLK_e:
        choice = 3;
        break;
    case SDLK_r:
        choice = 4;
        break;
    case SDLK_UP:
        choice = 5;
        break;
    case SDLK_DOWN:
        choice = 6;
        break;
    case SDLK_RIGHT:
        choice = 7;
        break;
    case SDLK_LEFT:
        choice = 8;
        break;
    default:
        break;
    }
}

void checkEditorMouseClickEvent(TGrid & grid, Uint8 button, int coordX, int coordY, int choice) {
    if (button == SDL_BUTTON_LEFT) {
        grid[coordX][coordY].type = choice;
    } else if(button == SDL_BUTTON_RIGHT) {
        grid[coordX][coordY].type = 0;
    }
}

void drawCursor(SDL_Surface *s, int mouseX, int mouseY, int choice) {

    if((mouseX && mouseY) != 0){
        switch (choice){

        case 1 :
            applySurface(mouseX, mouseY, surf_monstre, s, NULL);
            break;
        case 2:
            applySurface(mouseX, mouseY, surf_glacon, s, NULL);
            break;
        case 3:
            applySurface(mouseX, mouseY, surf_livre, s, NULL);
            break;
        case 4:
            applySurface(mouseX, mouseY, surf_dormeur, s, NULL);
            break;
        case 5:
            applySurface(mouseX, mouseY, surf_haut, s, NULL);
            break;
        case 6:
            applySurface(mouseX, mouseY, surf_bas, s, NULL);
            break;
        case 7:
            applySurface(mouseX, mouseY, surf_droite, s, NULL);
            break;
        case 8:
            applySurface(mouseX, mouseY, surf_gauche, s, NULL);
            break;
        }
    }
}

bool levelSelect(TGrid & grid, int mouseX, int mouseY) {
    int x = 0;
    int y = 0;
    bool found = false;
    while (x < 3 && y < 5 && !found) {
        int dx = mouseX - (62 + 90 * x), dy = mouseY - (160 + 80 * y);
        if (dx * dx + dy * dy <= 25 * 25) {
            loadLevel(grid, 3 * y + x + 1);
            found = true;
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
                fichier << type << std::endl;
            }
        }
        fichier.close();
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture." << std::endl;
    }
}

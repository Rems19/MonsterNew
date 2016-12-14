#include "grid.h"

/****************** Nom de la fonction **********************
* coordsToPixels                                            *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de convertir les coordonnées par rapport à la      *
* grille en coordonnées par rapport à la fenêtre en faisant *
* un passage par référence                                  *
*********************** Entrées *****************************
* int coordX int coordY: coordonnées par rapport à la grille*
* int & x, int & y: coordonnées par rapport à la fenêtre    *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void coordsToPixels(int coordX, int coordY, int & x, int & y) {
    x = MARGIN_LEFT + coordX * CASE_WIDTH;
    y = MARGIN_TOP + coordY * CASE_HEIGHT;
}

/****************** Nom de la fonction **********************
*  pixelsToCoords                                           *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de convertir les coordonnées par rapport à la      *
* fenêtre en coordonnées par rapport à la grille en faisant *
* un passage par référence                                  *
* -1 est affecté si le curseur n'est pas sur la grille      *
*********************** Entrées *****************************
* int x, int y: coordonnées par rapport à la fenêtre        *
* int &coordX int &coordY: coordonnées par rapport à la grille
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void pixelsToCoords(int x, int y, int & coordX, int & coordY) {
    if (x - MARGIN_LEFT < 0 || x > MARGIN_LEFT + WIDTH * CASE_WIDTH || y - MARGIN_TOP < 0 || y > MARGIN_TOP + HEIGHT * CASE_HEIGHT) {
        coordX = -1;
        coordY = -1;
    } else {
        coordX = (x - MARGIN_LEFT) / CASE_WIDTH;
        coordY = (y - MARGIN_TOP) / CASE_HEIGHT;
    }
}

/****************** Nom de la fonction **********************
* initGrid                                                  *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet d'initialiser les valeurs d'une grille passée en   *
* référence en la remplissant de case vide                  *
*********************** Entrées *****************************
* TGrid & grid: tableau de type Tgrid par référence         *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void initGrid(TGrid & grid) {
    for (int xCoord = 0; xCoord < WIDTH; xCoord++) {
        for (int yCoord = 0; yCoord < HEIGHT; yCoord++) {
            grid[xCoord][yCoord].type = EMPTY;
            grid[xCoord][yCoord].direction = NONE;
        }
    }
}

/****************** Nom de la fonction **********************
* draw                                                      *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de charger l'affichage des éléments de la grille   *
* dans la mémoire tampon en passant une surface par référence
*********************** Entrées *****************************
* TGrid & grid: tableau de type Tgrid(grille)               *
* SDL_Surface *s: pointeur vers surface de notre fenêtre    *
*********************** Sorties *****************************
*   ne retourne rien (référence)                            *
************************************************************/
void draw(TGrid grid, SDL_Surface *s) {
    int x = -1;
    int y = -1;

    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {

            coordsToPixels(i, j, x, y);

            switch (grid[i][j].direction) {

            case UP:
                applySurface(x + 5, y + 5, surf_haut, s, NULL);
                break;
            case DOWN:
                applySurface(x + 5, y + 5, surf_bas, s, NULL);
                break;
            case RIGHT:
                applySurface(x + 5, y + 5, surf_droite, s, NULL);
                break;
            case LEFT:
                applySurface(x + 5, y + 5, surf_gauche, s, NULL);
                break;
            default:
                break;
            }

            switch (grid[i][j].type) {

            case MONSTER:
                applySurface(x + 5, y, surf_monstre, s, NULL);
                break;
            case ICE:
                applySurface(x-2 , y - 8, surf_glacon, s, NULL);
                break;
            case BOOK:
                applySurface(x, y - 14, surf_livre, s, NULL);
                break;
            case SLEEPER:
                applySurface(x, y - 10, surf_dormeur, s, NULL);
                break;
            default:
                break;
            }
        }
    }
}

/****************** Nom de la fonction **********************
* loadLevel                                                 *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de charger un niveau à partir d'un fichier texte   *
* correspondant à un entier passé en paramètre              *
*********************** Entrées *****************************
*  TGrid & grid: tableau de type Tgrid par référence        *
* currentLevel: entier correspondant au niveau à charger    *
*********************** Sorties *****************************
* ne retourne rien (référence)              *
************************************************************/
void loadLevel(TGrid & grid, int currentLevel) {

    std::string lvl;
    CaseType caseType;
    Direction direction;
    int type;
    int dir;
    int x = 0;
    int y = 0;

    lvl = "levels/niveaux" + std::to_string(currentLevel) + ".txt";

    std::ifstream monFlux(lvl);  //Ouverture d'un fichier en lecture

    if(monFlux) {
        while(!monFlux.eof()) {
            monFlux >> type;
            monFlux >> dir;

            caseType = (CaseType) type;
            direction = (Direction) dir;

            grid[x][y].type = caseType;
            grid[x][y].direction = direction;


            if(y + 1  < HEIGHT) {
                y++;
            } else {
                y = 0;
                x++;
            }
        }
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." <<  std::endl;
    }
    monFlux.close();
}






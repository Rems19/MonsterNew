#include "editor.h"

/****************** Nom de la fonction **********************
* checkEditorKeyEvent                                       *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* se charge de modifier la sélection du type de case en     *
*       fonction de la touche du clavier pressé             *
*********************** Entrées *****************************
* La variable choice qui correspond au choix de la valeur de *
*                       la sélection                        *
*********************** Sorties *****************************
* ne retourne rien mais il y a modification de la variable  *
*                   choice par référence                    *
************************************************************/
void checkEditorKeyEvent(CaseType & choice) {

    Uint8 *keystates = SDL_GetKeyState( NULL ); //on récupère le status des touches (on considère que le programme
                                                //tourne suffisament vite pour ne jamais manquer des touches)

    if(keystates[SDLK_a]){
        choice = MONSTER;       //si on presse "a" , on sélectionne un monstre
    }
    if(keystates[SDLK_z]){
        choice = ICE;           //si on presse "z" , on sélectionne un glacon
    }
    if(keystates[SDLK_e]){
        choice = BOOK;          //si on presse "e" , on sélectionne un livre
    }
    if(keystates[SDLK_r]){
        choice = SLEEPER;       //si on presse "r" , on sélectionne un dormeur
    }
    if(keystates[SDLK_UP]){
        choice = UP_E;          //si on presse "UP" , on sélectionne une flèche vers le haut
    }
    if(keystates[SDLK_DOWN]){
        choice = DOWN_E;        //si on presse "DOWN" , on sélectionne une flèche vers le bas
    }
    if(keystates[SDLK_RIGHT]){
        choice = RIGHT_E;       //si on presse "RIGHT" , on sélectionne une flèche vers la droite
    }
    if(keystates[SDLK_LEFT]){
        choice = LEFT_E;        //si on presse "LEFT" , on sélectionne une flèche vers la gauche
    }
}

/****************** Nom de la fonction **********************
* checkEditorMouseClickEvent                                *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Récupère les évenements de la souris et modifie la grille *
*  en fonction de la position du curseur, de la selection   *
*                (choice), et des évènements                *
*********************** Entrées *****************************
* La grille en référence, les coordonnées de la souris      *
* (X et Y par rapport à la grille)                          *
*********************** Sorties *****************************
* La fonction ne retourne rien mais modifie la grille par   *
*                      référence                            *
************************************************************/
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

/****************** Nom de la fonction **********************
* drawCursor                                                *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Fonction qui affiche le type de case selectionné (l'image)*
*                 à coté du curseur                         *
*********************** Entrées *****************************
* La surface de l'écran                                     *
* Les coordonnées de la souris par rapport à la fenêtre     *
*********************** Sorties *****************************
* Ne retourne rien mais modifie la surface de l'ecran par   *
*                        référence                          *
************************************************************/
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

/****************** Nom de la fonction **********************
* levelSelect                                            *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de selectionner un niveau lorsque l'on va dans     *
*              l'éditeur de niveaux                         *
*********************** Entrées *****************************
* Coordonnées de la souris par rapport à la fenêtre         *
*********************** Sorties *****************************
* Retourne un entier correspondant au numéro selectionné    *
* 0 si aucun niveau n'est selectionné                       *
************************************************************/
int levelSelect(int mouseX, int mouseY) {
    int x = 0;
    int y = 0;
    int found = 0;
    while (x < 3 && y < 5 && found == 0) {                              //on test l'ensemble des boutons
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

/****************** Nom de la fonction **********************
* saveLevel                                                 *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de sauvegarder la grille en créant (ou écrasant) un*
* fichier texte correspondant au niveau sélectionné puis le *
* rempli d'entier correspondant au type de chaque           *
* case de la grille de notre niveau                         *
*********************** Entrées *****************************
* La grille                                                 *
* Le niveau selectionné                                     *
*********************** Sorties *****************************
* Ne retourne rien                                          *
************************************************************/
void saveLevel(TGrid grid, int level) {

    int type;

    std::string lvl;
    lvl = "levels/niveaux" + std::to_string(level) + ".txt";

    std::ofstream fichier(lvl,  std::ios::out |  std::ios::trunc);

    if(fichier) {
        for(int i = 0; i < WIDTH; i++) {
            for(int j = 0; j < HEIGHT; j++) {

                type = grid[i][j].type;             //on récupére le type de la case

                if(type == EMPTY)                   // si le type est EMPTY (0) alors on regarde si la case et une flèche ou non
                     switch(grid[i][j].direction) { // on regarde si une direction est assigné à la case
                     case UP:
                         type = UP_E;               //c'est une flèche vers le haut, type = 5
                         break;
                     case DOWN:
                         type = DOWN_E;             //c'est une flèche vers le bas, type = 6
                         break;
                     case RIGHT:
                         type = RIGHT_E;            //c'est une flèche vers la droite, type = 7
                         break;
                     case LEFT:
                         type = LEFT_E;             //c'est une flèche vers la gauche, type = 8
                         break;
                     default: break;                //si pas de direction on reste à zéro
                     }
                fichier << type << std::endl;
            }
        }
        fichier.close();
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture." << std::endl;
    }
}

#include "editor.h"


/****************** Nom de la fonction **********************
* checkEditorKeyEvent                                       *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* se charge de modifier la sélection du type de case en     *
*       fonction de la touche du clavier pressé             *
*********************** Entrées *****************************
* La variable choice qui correspond au choix de la valeur de*
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
* Xavier                                                    *
********************* Description ***************************
* Récupère les évenements de la souris et modifie la grille *
*  en fonction de la position du curseur, de la selection   *
*                (choice), et des évènements                *
*********************** Entrées *****************************
* La grille en référence, les coordonnées de la souris      *
* (X et Y par rapport à la grille)                          *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void checkEditorMouseClickEvent(TGrid & grid, int coordX, int coordY, CaseType choice) {

    Uint8 mousestates = SDL_GetMouseState(NULL,NULL);

    if ( coordX != -1 && coordY != -1) {
        if (mousestates &SDL_BUTTON_LEFT ) {

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
}

/****************** Nom de la fonction **********************
* drawCursor                                                *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Fonction qui charge l'affichage du de la case selectionné *
*  (l'image) à coté du curseur en modifiant la surface      *
*                        screen par référence               *
*********************** Entrées *****************************
* SDL_Surface *s: La surface de l'écran                     *
* int mouseX, int mouseY: Les coordonnées de la souris par  *
*                         rapport à la fenêtre              *
*  int choice : la valeur du type de la case sélectionnée   *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void drawCursor(SDL_Surface *s, int mouseX, int mouseY, int choice, int modeEditor) {

    if((mouseX && mouseY) != 0) {

        switch (choice) {

        case MONSTER :
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_monstre, s, NULL);
            else
                applySurface(385,13,surf_cursor,s, NULL);
            break;
        case ICE:
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_glacon, s, NULL);
            else
                applySurface(385,83,surf_cursor,s, NULL);
            break;
        case BOOK:
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_livre, s, NULL);
            else
                applySurface(385,153,surf_cursor,s, NULL);
            break;
        case SLEEPER:
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_dormeur, s, NULL);
            else
                applySurface(385,223,surf_cursor,s, NULL);
            break;
        case UP_E:
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_haut, s, NULL);
            else
                applySurface(385,433,surf_cursor,s, NULL);
            break;
        case DOWN_E:
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_bas, s, NULL);
            else
                applySurface(385,503,surf_cursor,s, NULL);

            break;
        case RIGHT_E:
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_droite, s, NULL);
            else
                applySurface(385,363,surf_cursor,s, NULL);
            break;
        case LEFT_E:
            if(modeEditor == 1)
                applySurface(mouseX, mouseY, surf_gauche, s, NULL);
            else
                applySurface(385,293,surf_cursor,s, NULL);

            break;
        }

    }
}

/****************** Nom de la fonction **********************
* levelSelect                                               *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Permet de selectionner un niveau lorsque l'on va dans     *
*              l'éditeur de niveaux                         *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
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
* Xavier                                                    *
********************* Description ***************************
* Permet de sauvegarder la grille en créant (ou écrasant) un*
* fichier texte correspondant au niveau sélectionné puis le *
* rempli d'entier correspondant au type de chaque           *
* case de la grille de notre niveau                         *
*********************** Entrées *****************************
* TGrid grid : tableau  de deux dimensions contenant une    *
*              direction et un type                         *
* int level : entier contenant le niveau à sauvegarder      *
*********************** Sorties *****************************
* Ne retourne rien                                          *
************************************************************/
void saveLevel(TGrid grid, int level) {

    int type;
    int direction;

    std::string lvl;
    lvl = "levels/niveaux" + std::to_string(level) + ".txt";

    std::ofstream fichier(lvl,  std::ios::out |  std::ios::trunc);

    if(fichier) {
        for(int i = 0; i < WIDTH; i++) {
            for(int j = 0; j < HEIGHT; j++) {

                type = grid[i][j].type;                             //on récupère le type de la case
                direction = grid[i][j].direction;                   //on recupère la direction de la case
                fichier << type << " " << direction << std::endl;   //on écrit les valeurs dans le fichier texte
            }
        }
        fichier.close();
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture." << std::endl;
    }
}

/****************** Nom de la fonction **********************
* isMouseOnEditorLevelButton                                *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Permet de savoir si la souris est positionnée sur le      *
* bouton d'aide (éditeur) en renvoyant True or False        *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
*********************** Sorties *****************************
* retourne un booléen                                       *
************************************************************/
bool isMouseOnEditorHelpButton(int mouseX, int mouseY) {
    // help button center : 242, 534, radius : 22
    int dx = mouseX - 242;
    int dy = mouseY - 534;

    return dx * dx + dy * dy <= 22 * 22;
}


/****************** Nom de la fonction **********************
* isMouseOnSelectButton                                *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Permet de savoir si la souris est positionnée sur le      *
* bouton d'aide (éditeur) en renvoyant True or False        *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
*********************** Sorties *****************************
* retourne un booléen                                       *
************************************************************/
bool isMouseOnSelectButton(int mouseX, int mouseY, int i) {
    // help button center : 242, 534, radius : 22
    int dx = mouseX - 370;
    int dy = mouseY - (40 + i * 70);

    return dx * dx + dy * dy <= 30 * 30;
}

/****************** Nom de la fonction **********************
* isMouseOnModeButton                                       *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Permet de savoir si la souris est positionnée sur le      *
* bouton de changement de mode (éditeur)                    *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
*********************** Sorties *****************************
* retourne un booléen                                       *
************************************************************/
bool isMouseOnModeButton(int mouseX, int mouseY) {
    // mode button x1 : 280, x2:320,y1 : 0 y2: 40
    return mouseX < 320 && mouseY < 40 && 0 < mouseY && 280 < mouseX;
}


/****************** Nom de la fonction **********************
* setEditorForeground                                       *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Permet de charger la surface correspondant à l'aide sur la*
* surface screen si la souris est sur le bouton aide        *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
* SDL_Surface *s: La surface de l'écran                     *
*********************** Sorties *****************************
* ne retoune rien                                           *
************************************************************/
void setEditorForeground(SDL_Surface *screen, int mouseX, int mouseY, int modeEditor) {

    if (isMouseOnEditorHelpButton(mouseX, mouseY)) {
        setScreenBackground(screen, surf_Transparency);
        if(modeEditor == 1 ) {
            setScreenBackground(screen,  surf_EditorHelp);
        } else {
            setScreenBackground(screen,  surf_EditorHelp2);
        }

    }
}


/****************** Nom de la fonction **********************
* setSelectCursor                                           *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Permet de charger la selection quand on est sur la case   *
* correspondante (mode 2)                                   *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
* CaseType & choice: variable de la selection               *
*********************** Sorties *****************************
* ne retoune rien                                           *
************************************************************/
void setSelectCursor(int mouseX, int mouseY, CaseType & choice) {

    for(int i = 0; i  < 8; i++) {

        if(isMouseOnSelectButton(mouseX, mouseY, i)) {
            switch (i) {
            case 0:
                choice = MONSTER;
                break;
            case 1:
                choice = ICE;
                break;
            case 2:
                choice = BOOK;
                break;
            case 3:
                choice = SLEEPER;
                break;
            case 4:
                choice = LEFT_E;
                break;
            case 5:
                choice = RIGHT_E;
                break;
            case 6:
                choice = UP_E;
                break;
            case 7:
                choice = DOWN_E;
                break;
            }
        }
    }
}

/****************** Nom de la fonction **********************
* setEditorBackground                                       *
******************** Auteur , Dates *************************
* Xavier                                                    *
********************* Description ***************************
* Permet de charger la surface correspondant à l'aide sur la*
* surface screen en fonction du mode de selection           *
*********************** Entrées *****************************
*int mouseX, int mouseY: Coordonnées de la souris par rapport
*                        à la fenêtre                       *
* SDL_Surface *s: La surface de l'écran                     *
*********************** Sorties *****************************
* ne retoune rien                                           *
************************************************************/
void setEditorBackground(SDL_Surface *screen, int modeEditor) {

    if (modeEditor == 1) {
        setScreenBackground(screen, surf_backgroundEditor);
    } else {
        setScreenBackground(screen,  surf_backgroundEditor2);
    }
}





#include <iostream>
#include "main.h"
#include "affichage/screen.h"
#include "menu/menu.h"
#include "game/grid.h"
#include "editor/editor.h"
#include "affichage/surfaces.h"

using namespace std;

int main() {

    bool quit = false;                  //Initialisation de quit à false qui nous permet de faire tourner ou arrêter notre programme

    State state = MENU;                 //Initialisation du statut du programme au MENU

    int currentLevel = 1;               //Initialisation de currentLevel qui correspond au niveau actuel lors du déroulement du jeu

    int levelEdit = 0;                  //Initilisation de levelEdit qui correspond au niveau sélectionné pour l'édition (par défaut 0 = pas de selection)

    int maxLevel = 15;                  //Initialisation du nombre de niveau maximum que l'on veut jouer ( de 1 au nombre max de niveau )

    CaseType choice = MONSTER;          //Initialisation de la variable choice qui correspond à l'élement sélectionné dans l'éditeur (par défaut le monstre)

    Direction direction = NONE;         //Initialisation d'une variable Direction qui sert au déplacement du monstre

    initSDL();                          //Initialisation de l'ensemble des fonctions relatives à la SDL

    SDL_Surface* screen;                //initialisation d'une surface propre à la SDL qui sera la surface principale affichée dans notre fenêtre
    initScreen(screen);                 //initialisation des paramètres de la fenêtre

    loadSurfaces();                     //chargement des surfaces du jeu
    initMenu();                         //chargement des surfaces du menu

    TGrid grid;                         //Initialisation de la grille
    initGrid(grid);                     //Initialisation du contenu de la grille

    SDL_Event event;                    //initialisation d'une variable d'évènement propre à la SDL
    int mouseX, mouseY;                 // Cursor coordinates in pixels
    int mouseXCoord, mouseYCoord;       // Coordinates of the case pointed by the cursor

    // SDL_SetAlpha(surf_background,SDL_SRCALPHA , 125)    ; //ajoute un effet intéressant à voir

    while ( !quit && SDL_WaitEvent(&event) ) {

        SDL_PollEvent(&event);                                          // on récupère les évênements dans event

        switch (event.type) {                                           //on fait un switch pour gérer les différents évènements

        case SDL_QUIT:                                                  //si il y a un évènement "quitter"

            quit = true;                                                //quit passe à true on ferme le programme
            break;

        case SDL_MOUSEMOTION:                                           //si la souris à bougé

            mouseX = event.button.x;                                    //on met à jour sa coordonnée en x par rapport à la fenêtre
            mouseY = event.button.y;                                    //on met à jour sa coordonnée en y par rapport à la fenêtre
            pixelsToCoords(mouseX, mouseY, mouseXCoord, mouseYCoord);   //on met à jour ses coordonnée x et y par rapport à la grille
            break;

        case SDL_MOUSEBUTTONUP:                                         //si on lache un bouton de la souris

            switch (event.button.button) {                              //switch pour agir en fonction du bouton qui a été relaché

            case SDL_BUTTON_LEFT:                                       //s'il s'agit du bouton gauche de la souris

                if (state == MENU) {                                    //si nous sommes dans le menu :

                    if (isMouseOnPlayButton(mouseX, mouseY)) {              //si la souris est sur le bouton play
                        loadLevel(grid, 1);                                 //on charge le niveau 1
                        state = GAME;                                       //on change le statut du programme pour lancer le jeu

                    } else if (isMouseOnEditButton(mouseX, mouseY))     //sinon si la souris et sur le bouton d'édition
                        state = EDITOR_MENU;                                //on change le statut du programme pour lancer le selecteur de niveau

                    else if (isMouseOnQuitButton(mouseX, mouseY))       //sinon si la souris est sur le bouton quitter
                        quit = true;                                        // on affecte true à quitter pour quitter le programme

                } else if (state == EDITOR_MENU) {                      //si nous sommes dans le menu de selection de niveau pour l'éditeur :

                    levelEdit = levelSelect(mouseX, mouseY);                //on affecte le niveau selectionné à levelEdit
                    if(levelEdit != 0) {                                    //si un niveau a été sélectionné
                        loadLevel(grid, levelEdit);                         //on charge le niveau correspondant
                        state = EDITOR_GRID;                                //on change le statut du programme  pour lancer l'éditeur
                    }

                } else if (state == GAME) {                             //si nous sommes dans le jeu :

                    if(isMouseOnGameResetButton(mouseX, mouseY)) {          //si la souris est sur le bouton reset
                        initGrid(grid);                                     //on réinitialise la grille par sécurité
                        loadLevel(grid, currentLevel);                      //on charge le niveau actuel
                    }

                } else if (state == EDITOR_GRID) {                      //si nous sommes dans l'éditeur de niveau :

                    if(isMouseOnGameResetButton(mouseX, mouseY)) {          //si la souris est sur le bouton de sauvegarde (même position que "reset")
                        saveLevel(grid, levelEdit);                         //on sauvegarde le niveau
                        state = MENU;                                       //on chage le statut du jeu pour repasser dans le menu
                    }
                }
                break;

            default: break;
            }
            break;

        case SDL_KEYDOWN:                                               //si une touche est pressée

            switch(event.key.keysym.sym) {                              //on fait un switch pour gérer l'ensemble des touches

            case SDLK_ESCAPE:                                           //si la touche espace est pressée

                if(state == MENU) {                                     //si l'on est dans le menu
                    quit = true;                                        // on affecte true à quitter pour quitter le programme

                } else {                                                //si on est ailleur on revient au menu
                    if (state == EDITOR_GRID)                           //si nous sommes dans l'éditeur de niveau
                        saveLevel(grid, levelEdit);                     //on sauvegarde le niveau

                    state = MENU;                                       //on change le statut du jeu pour repasser dans le menu
                }
                break;

            default: break;
            }
            break;

        default: break;
        }


        if (state == MENU) {                                                        //si on est dans le menu

            setScreenBackground(screen, getMenuBackground(mouseX, mouseY));         //on affiche le fond du mene qui varie avec la fonction getMenuBackground
            currentLevel = 1;                                                       //on réinitialise le currentLevel pour recommencer du début
            levelEdit = 0;                                                          //on réinitialise levelEdit à 0 pour annuler la sélection précédente (pour l'editeur)

        } else if (state == GAME) {                                                 //si on est dans le jeu

            mouvement(grid, event, direction, screen, mouseXCoord, mouseYCoord, currentLevel); // on se charge du déplacement du monstre
            setScreenBackground(screen, surf_background);                           //on charge le fond relatif au jeu
            draw(grid, screen);                                                     //on charge l'affichage de la grille dans la surface screen
            levelWin(grid, screen, currentLevel, state, maxLevel);                  //on lance levelWin qui permet de vérifier si
                                                                                    //l'on a gagné ou non et d'agir en conséquence

        } else if (state == EDITOR_GRID) {                                          //si on est dans l'éditeur de niveaux

            setScreenBackground(screen, surf_backgroundEditor);                     //on affiche le background de l editeur
            draw(grid, screen);                                                     //on affiche les éléments de la grille
            drawCursor(screen, mouseX, mouseY, choice);                             //on affiche la sélection à coté du curseur
            setScreenBackground(screen, getEditorForeground(mouseX, mouseY));       //on superpose l'aide au background si on passe la souris sur le bouton help

            checkEditorKeyEvent(choice);                                            //on gère les évènements relatifs au clavier
            checkEditorMouseClickEvent(grid, mouseXCoord, mouseYCoord, choice);     //on gère les évènements relatifs à la souris

        } else {                                                                    //si on est dans la selection du niveau à éditer

            setScreenBackground(screen, surf_editorLevelChoice);                    //on affiche le fond de selection de niveau
        }

        updateScreen(screen);                                                       //on met à jour la fenêtre en affichant l'image en mémoire tampon
    }

    SDL_FreeSurface(screen);                                                        //on nettoie la surface principale screen
    freeMenuSurfaces();                                                             //on nettoie toutes les surfaces du menu
    freeSurfaces();                                                                 //on nettoie toutes les surfaces du jeu

    return EXIT_SUCCESS;                                                            //on retourne EXIT_SUCCESS lors de la fermeture du programme
}


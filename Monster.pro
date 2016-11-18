TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra
SOURCES += main.cpp \
    affichage/screen.cpp \
    grid.cpp \
    affichage/sdl_funcs.cpp \
    menu.cpp

LIBS += `sdl-config --libs` -lSDL_image -lSDL_ttf

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    affichage/screen.h \
    grid.h \
    affichage/sdl_funcs.h \
    menu.h

DISTFILES += \
    assets/background.bmp \
    assets/backgroundRedux.bmp \
    assets/menu.bmp \
    assets/menuetedit.bmp \
    assets/sprite.bmp \
    assets/winEndSprite.bmp \
    assets/winSprite.bmp \
    assets/bas.png \
    assets/dormeur.png \
    assets/droite.png \
    assets/gauche.png \
    assets/glacon.png \
    assets/haut.png \
    assets/livre.png \
    assets/monstre.png \
    assets/menuetedit_edit.bmp \
    assets/menuetedit_play.bmp \
    assets/menuetedit_quit.bmp


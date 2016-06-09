#pragma once

#include <3ds.h>
#include <sf2d.h>

char appDirPath[100];
char allappsPath[250];
char allapps_pressedPath[250];
char apolloPath[250];
char browserPath[250];
char clockPath[250];
char fmPath[250];
char galleryPath[250];
char gamePath[250];
char messagesPath[250];
char settingsPath[250];

sf2d_texture *backdrop;

sf2d_texture *ic_launcher_clock;
sf2d_texture *ic_launcher_filemanager;
sf2d_texture *ic_launcher_gallery;
sf2d_texture *ic_launcher_game;

void appDrawerUnload();
int appDrawer();
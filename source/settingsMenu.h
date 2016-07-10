#pragma once

#include <3ds.h>
#include <stdio.h>
#include <string.h>

#define YEAR ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
+ (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))

#define MONTH (__DATE__ [2] == 'n' ? 0 \
: __DATE__ [2] == 'b' ? 1 \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 2 : 3) \
: __DATE__ [2] == 'y' ? 4 \
: __DATE__ [2] == 'n' ? 5 \
: __DATE__ [2] == 'l' ? 6 \
: __DATE__ [2] == 'g' ? 7 \
: __DATE__ [2] == 'p' ? 8 \
: __DATE__ [2] == 't' ? 9 \
: __DATE__ [2] == 'v' ? 10 : 11)

#define DAY ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 \
+ (__DATE__ [5] - '0'))

#define DATE_AS_INT (((YEAR - 2000) * 12 + MONTH) * 31 + DAY

sftd_font *robotoSettingsMenu;

sf2d_texture *recoverybg;
sf2d_texture *loading;

sf2d_texture *highlight;

sf2d_texture *aboutBg;
sf2d_texture *developerBg;
sf2d_texture *displayBg;
sf2d_texture *performanceBg;
sf2d_texture *performanceBg2;
sf2d_texture *securityBg;
sf2d_texture *settingsBg;
sf2d_texture *updatesBg;
sf2d_texture *wifiBg;

sf2d_texture *about_highlight;
sf2d_texture *display_highlight;
sf2d_texture *developeroptions_highlight;
sf2d_texture *performance_highlight;
sf2d_texture *security_highlight;
sf2d_texture *wifi_highlight;

sf2d_texture *onSwitch;
sf2d_texture *offSwitch;
sf2d_texture *select;
sf2d_texture *deselect;

int language, hrTime, DARK, experimentalF, screenDisplay;
unsigned int fontColor;

int updatesMenu();
void onlineUpdater();
void flashUpdate();
int aboutMenu();
int developerMenu();
int displayMenu();
int displayThemes();
int displayIconPack();
void replaceAsset(char tempData[], char path[], char imgPath[], char redirectPath[]);
void iconPackLoad();
void iconPackReload();
int displayTime();
int performanceMenu();
int storageMenu();
int batteryMenu();
int securityMenu();
int settingsHighlight(int style);
int settingsUnload();
int settingsMenu();
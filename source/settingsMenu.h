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

char settingsBgPath[250], displayBgPath[250], aboutBgPath[250], developerBgPath[250], performanceBgPath[250], performance2BgPath[250], 
	 securityBgPath[250], updatesBgPath[250];

char highlightPath[250], offSwitchPath[250], onSwitchPath[250], selectPath[250];

char aboutPath[250], developerPath[250], performancePath[250], securityPath[250], themesPath[250], wifiPath[250];

char cursorPath[250];

char fmBgPath[250], fmSelectorPath[250], diriconPath[250];

char quickSettingsBgPath[250], navbarPath[250], backdropPath[250], navbarHighlightPath[250];

char backgroundPath[500], themeDirPath[250];

char rgbValuesPath[250], settingsFontColorPath[200];

struct settingsFontColor 
{
   int	r;
   int	g;
   int	b;
};

int language, hrTime, DARK, experimentalF, screenDisplay, widgetActivator, bootAnimActivator, firstBoot, r, g, b;
unsigned int fontColor;

void flashUpdate();
int aboutMenu();
int developerMenu();
int displayMenu();
int displayThemes();
int displayThemesManager();
int displayIconPack();
void replaceAsset(char tempData[], char path[], char imgPath[], char redirectPath[]);
void themesLoad();
void themesReload();
void iconPackLoad();
void iconPackReload();
int displayTime();
int displayMiscellaneous();
int performanceMenu();
int storageMenu();
int batteryMenu();
int securityMenu();
int settingsHighlight(int style);
int settingsUnload();
int settingsMenu();
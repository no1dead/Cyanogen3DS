#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>

#include "Roboto_ttf.h"

sftd_font *roboto;
sftd_font *robotoWidget1;
sftd_font *robotoWidget2;

sf2d_texture *background;
sf2d_texture *cursor;
sf2d_texture *quickSettings;

//App icon assets
sf2d_texture *ic_allapps;
sf2d_texture *ic_allapps_pressed;
sf2d_texture *ic_launcher_browser;
sf2d_texture *ic_launcher_messenger;
sf2d_texture *ic_launcher_apollo;
sf2d_texture *ic_launcher_settings;

// Navbar Assets
sf2d_texture *navbar;
sf2d_texture *backicon;
sf2d_texture *homeicon;
sf2d_texture *multicon;

// Battery Icon assets (1-5)
sf2d_texture *_100;
sf2d_texture *_80;
sf2d_texture *_60;
sf2d_texture *_40;
sf2d_texture *_20;
sf2d_texture *_charge;

//Wifi icons
sf2d_texture *wifiIconFull;
sf2d_texture *wifiIconNull;

// Widget Assets
sf2d_texture *dayWidget;
sf2d_texture *nightWidget;

u16 touch_x;
u16 touch_y;
touchPosition touch;
touchPosition oldTouch, firstTouch;
u16 touchTimer;

int cursorController();
int batteryStatus(int x, int y);
void appDrawerIcon();
int navbarControls(int type);
void androidQuickSettings();
int dayNightWidget();
int home();

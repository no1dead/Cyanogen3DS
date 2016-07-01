#pragma once

#include <3ds.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#define WHITE RGBA8(255, 255, 255, 255)
#define LITEGRAY RGBA8(191, 191, 191, 255)
#define BLACK RGBA8(0, 0, 0, 255)
#define TEAL RGBA8(0, 149, 135, 255)

#define SOC_ALIGN       0x1000
#define SOC_BUFFERSIZE  0x100000

char tempMessage[20];
char tempPin[5];
char tempData[250];

int bilinearFilterEnabled;

u8 getModel();
u8 getRegion();
u8 getLang();
bool detectSD();
const char * getUsername();
int getBirthday();
bool touchPressed(touchPosition p);
char * getMacAddress();
gfxScreen_t switchDisplay(int display);
u32 soc_init(void);
u32 soc_exit(void);
//bool isWifiEnabled();
int downloadFile(const char* url, const char* path);
void setBilinearFilter(int enabled, sf2d_texture *texture);
int extractZip(const char * zipFile, const char * path);
void createDirs();
int setFileDefaultsInt(char *path, int value, int var);
float setFileDefaultsFloat(char *path, float value, float var);
char * setFileDefaultsChar(char path[], char data[], char var[]);
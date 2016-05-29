#pragma once

#include <3ds.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define WHITE RGBA8(255, 255, 255, 255)
#define LITEGRAY RGBA8(191, 191, 191, 255)
#define BLACK RGBA8(0, 0, 0, 255)
#define TEAL RGBA8(0, 149, 135, 255)

char tempMessage[20];
char tempPin[5];
char tempData[250];

u8 getModel();
u8 getRegion();
u8 getLang();
int setCPU();
int getCPU();
bool detectsd();
const char * getUsername();
int getBirthday();
int setFileDefaultsInt(char *path, int value, int var);
float setFileDefaultsFloat(char *path, float value, float var);
char * setFileDefaultsChar(char path[], char data[], char var[]);
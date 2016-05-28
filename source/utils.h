#pragma once

#include <3ds.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
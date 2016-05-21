#pragma once

#include <3ds.h>
#include <string.h>
#include <stdlib.h>

u8 getModel();
u8 getRegion();
u8 getLang();
int setCPU();
int getCPU();
bool detectsd();
const char * getUsername();
int getBirthday();
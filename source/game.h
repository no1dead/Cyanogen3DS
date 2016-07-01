#pragma once

#include <3ds.h>
#include <stdio.h>
#include <string.h>

#define CTR_BUFSIZE 64*1024

/*These are mostly based off of rinnegatamte's lua player plus src code. 
I will alter these to my needs later.*/

int launchApp(u64 titleId);
char * getCardID();
int launch3DSX(char * path);
int installCIA(const char *path);
int launchCia(u64 titleID, FS_MediaType mediaType);
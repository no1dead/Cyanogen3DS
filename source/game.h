#pragma once

#include <3ds.h>
#include <stdio.h>
#include <string.h>

#define CTR_BUFSIZE 64*1024

/*These are mostly based off of rinnegatamte's lua player plus src code. 
I will alter these to my needs later.*/

typedef struct
{
	u8 mediatype;
	u64 title_id;
}titleInfo_s;

int launch3DSX(const char * path);
int launchApp(u64 titleId);
char * getCardID();
int installCIA(const char *path);
int launchCia(u64 titleID, FS_MediaType mediaType);
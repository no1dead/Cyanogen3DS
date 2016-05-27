#pragma once

#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

u8* buffer;
u32 size;

void audio_load(const char *audio);
void audio_stop(void);
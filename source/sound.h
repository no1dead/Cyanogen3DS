#pragma once

#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct audio 
{
    u8* sndbuffer;
    u32 sndsize;
    int channel;
    bool loaded;
    int duration;
} audio;

audio camera_click;
audio KeypressStandard;
audio Lock;
audio Unlock;

bool audioActive;
bool waitForSounds;

void audio_load(const char *audio1, audio * sound);
void audioPlay(audio * sound, bool loop);
void audioFree(audio * sound);
void audio_stop(void);
char* concat(char *s1, char *s2);
void waitForSoundToFinishPlaying(audio * sound);
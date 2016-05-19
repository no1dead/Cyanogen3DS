#include "sound.h"

void audio_load(const char *audio1, audio * sound)
{
	FILE *file = fopen(audio1, "rb");
	if(file != NULL && audioActive)
	{
		fseek(file, 0, SEEK_END);
		sound->sndsize = ftell(file);
		fseek(file, 0, SEEK_SET);
		sound->sndsize = sound->sndsize - 0x48;
		fseek(file, 0x48, SEEK_SET);
		sound->sndbuffer = linearAlloc(sound->sndsize);
		fread(sound->sndbuffer, 1, sound->sndsize, file);
		fclose(file);
		if (sound->sndbuffer != NULL) 
		{
            sound->loaded = true;
		}
		else 
		{
            sound->loaded = false;
		}
	}
	else
	{
        sound->loaded = false;
	}

	if (sound->loaded) 
	{
        sound->duration = sound->sndsize / 88244;
	}
	else 
	{
        sound->duration = 0;
	}
}

void audioPlay(audio * sound, bool loop) 
{
	if (sound->loaded && audioActive)
	{
		u32 flags;

		if (loop) 
		{
			flags = SOUND_FORMAT_16BIT | SOUND_REPEAT;
		}
		else 
		{
			flags = SOUND_FORMAT_16BIT;
		}
		
		csndPlaySound(sound->channel, flags, 44100, 1, 0, sound->sndbuffer, sound->sndbuffer, sound->sndsize);
	}
}

void audioFree(audio * sound) 
{
    if (audioActive) 
	{
		memset(sound->sndbuffer, 0, sound->sndsize);
        GSPGPU_FlushDataCache(sound->sndbuffer, sound->sndsize);
        linearFree(sound->sndbuffer);
    }
}

void audio_stop(void)
{
    if (audioActive) 
	{
        csndExecCmds(true);

        CSND_SetPlayState(0x8, 0);
        CSND_SetPlayState(0x9, 0);
        CSND_SetPlayState(0x10, 0);

        csndExecCmds(true);

        audioFree(&camera_click);
        audioFree(&KeypressStandard);
        audioFree(&Lock);
        audioFree(&Unlock);

        csndExecCmds(true);
    }
}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    //in real code you would check for errors in malloc here.
	//perhaps this should be done?
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void waitForSoundToFinishPlaying(audio * sound) 
{
    if (waitForSounds && sound->loaded) 
	{
        u8 playing = 0;
        csndIsPlaying(sound->channel, &playing);
        while (playing == 1) 
		{
            csndIsPlaying(sound->channel, &playing);
        }
    }
}

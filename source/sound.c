#include "sound.h"

void audio_load(const char *audio)
{
	FILE *file = fopen(audio, "rb");
	fseek(file, 0, SEEK_END);
	off_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = linearAlloc(size);
	//off_t bytesRead = fread(buffer, 1, size, file);
	fclose(file);
	csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_ONE_SHOT, 48000, 1, 0, buffer, buffer, size);
	linearFree(buffer);
}

void audio_stop(void)
{
	csndExecCmds(true);
	CSND_SetPlayState(0x8, 0);
	memset(buffer, 0, size);
	GSPGPU_FlushDataCache(buffer, size);
	linearFree(buffer);
}
#include "utils.h"
#include "fileManager.h"

u16 OLD_3DS_CLOCK = 268;
u16 NEW_3DS_CLOCK = 804;
int currentClock = 0;

u8 getModel()
{
	u8 model = 0;
	CFGU_GetSystemModel(&model);
	
	return model;
}

u8 getRegion()
{
	u8 region = 0;
	CFGU_SecureInfoGetRegion(&region);
	
	return region;
}

u8 getLang()
{
	u8 language;
	CFGU_GetSystemLanguage(&language);
	
	return language;
}

int setCPU(int cpu)
{
	u16 cpuClock = cpu;
	bool isNew;
	APT_CheckNew3DS((u8*)&isNew);
	
	if (cpuClock >= NEW_3DS_CLOCK && isNew)
	{
		osSetSpeedupEnable(1);
		currentClock = NEW_3DS_CLOCK;
	}
	else 
	{
		osSetSpeedupEnable(0);
		currentClock = OLD_3DS_CLOCK;
	}
	
	return 0;
}

int getcpu()
{
	return currentClock;
}

bool detectsd()
{
	bool isSD;
	FSUSER_IsSdmcDetected(&isSD);
	return isSD;
}

const char * getUsername()
{
	const u16 *block = malloc(0x1C);
	
	CFGU_GetConfigInfoBlk2(0x1C, 0xA0000, (u8*)block);
	u8 *name = malloc(0x14);
	ssize_t len = utf16_to_utf8(name, block, 0x14);
	
	if (len < 0) 
	{
		return NULL;
	}
	
	return (const char *)name; // The username is only 0x14 characters long.
}

int getBirthday()
{
	u8 birthday[0x02];
	//u8 b1, b2;
	CFGU_GetConfigInfoBlk2(0x02, 0xA0001, (u8*)&birthday);
	//b1 = birthday[0x01];
	//b2 = birthday[0x00];
	
	return 0;
}

int setFileDefaultsInt(char *path, int value, int var)
{
	FILE *temp;
	 
	if (!(fileExists(path, &sdmcArchive)))
	{
		temp = fopen(path, "w");
		fprintf(temp, "%d", value);
		fclose(temp);
	} 
	
	temp = fopen(path, "r");
	fscanf(temp, "%d", &var);
	fclose(temp);
	
	return var;
}

float setFileDefaultsFloat(char *path, float value, float var)
{
	FILE *temp;
	 
	if (!(fileExists(path, &sdmcArchive)))
	{
		temp = fopen(path, "w");
		fprintf(temp, "%f", value);
		fclose(temp);
	} 
	
	temp = fopen(path, "r");
	fscanf(temp, "%f", &var);
	fclose(temp);
	
	return var;
}

char * setFileDefaultsChar(char path[], char data[], char var[])
{
	FILE * temp;
	
	if (!(fileExists(path, &sdmcArchive)))
	{
		temp = fopen(path, "w");
		fprintf(temp, "%s", data);
		fclose(temp);
	}
	
	temp = fopen(path, "r");
	fscanf(temp, "%s", var);
	fclose(temp);
	
	return var;
}
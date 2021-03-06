#include "appDrawer.h"
#include "archive.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "settingsMenu.h"
#include "utils.h"

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

bool detectSD()
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

bool touchPressed(touchPosition p)
{
    //I don't think either of these are ever 0
    //unless the screen isn't touched.
    if(p.px>0 || p.py>0)
        return true;

    return false;
}

gfxScreen_t switchDisplay(int display)
{
	if (display == 0)
		return GFX_TOP;
	else
		return GFX_BOTTOM;
}

char * getMacAddress()
{
	u8* macByte = (u8*)0x1FF81060; 
	static char macAddress[18];
	sprintf(macAddress,"%02X:%02X:%02X:%02X:%02X:%02X",*macByte,*(macByte+1),*(macByte+2),*(macByte+3),*(macByte+4),*(macByte+5));
	macAddress[17] = 0;
	
	return macAddress;
}

static u32 *SOC_buffer = 0;

u32 soc_init(void) 
{
	Result ret;
	u32 result = 0;
	
	SOC_buffer = (u32*)memalign(SOC_ALIGN, SOC_BUFFERSIZE);
	if (SOC_buffer != 0) 
	{
		ret = socInit(SOC_buffer, SOC_BUFFERSIZE);
		if (ret == 0) 
		{
			result = 1;
		} 
		else 
		{
			free(SOC_buffer);
		}
	}
	return result;
}

u32 soc_exit(void) 
{
	if (SOC_buffer) 
	{
		socExit();
		free(SOC_buffer);
		SOC_buffer = 0;
	}
	return 0;
}

void setBilinearFilter(int enabled, sf2d_texture *texture)
{
	bilinearFilterEnabled = enabled;
	if (enabled == 1)
	{
		sf2d_texture_set_params(texture, GPU_TEXTURE_MAG_FILTER(GPU_LINEAR) | GPU_TEXTURE_MIN_FILTER(GPU_NEAREST));
	}
}

int extractZip(const char * zipFile, const char * path) 
{
	FS_Archive sdmcArchive = 0;
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	FS_Path tempPath = fsMakePath(PATH_ASCII, path);
	FSUSER_CreateDirectory(sdmcArchive, tempPath, FS_ATTRIBUTE_DIRECTORY);
	FSUSER_CloseArchive(sdmcArchive);
	char tmpFile2[1024];
	char tmpPath2[1024];
	strcpy(tmpPath2, "sdmc:");
	strcat(tmpPath2, (char *)path);
	chdir(tmpPath2);
	if (strncmp("romfs:/", zipFile, 7) == 0) 
		strcpy(tmpFile2, zipFile);
	else
	{
		strcpy(tmpFile2, "sdmc:");
		strcat(tmpFile2, (char*)zipFile);
	}
	Zip *handle = ZipOpen(tmpFile2);
	if (handle == NULL) 
		return 0;
	int result = ZipExtract(handle, NULL);
	ZipClose(handle);
	return result;
}

void installRequiredFiles()
{
	/*if (fileExists("/3ds/Cyanogen3DS/UPDATE.zip"))
		deleteFile("/3ds/Cyanogen3DS/UPDATE.zip"); //Delete any existing UPDATE.zip.*/
	
	if (!(dirExists("/3ds/Cyanogen3DS/screenshots")))
		makeDir("/3ds/Cyanogen3DS/screenshots");
	
	if (!(dirExists("/3ds/Cyanogen3DS/system/themes")))
		makeDir("/3ds/Cyanogen3DS/system/themes");
	
	if (!(dirExists("3ds/Cyanogen3DS/system/app/clock")))
		makeDir("/3ds/Cyanogen3DS/system/app/clock");
}

void installFontColorData()
{
	FILE * file;
	
	if (!(fileExists(appDrawerFontColorPath)))
	{
		file = fopen(appDrawerFontColorPath, "w");
		fprintf(file, "0\n0\n0");
		fclose(file);
	}
	
	if (!(fileExists(clockWidgetFontColorPath)))
	{
		file = fopen(clockWidgetFontColorPath, "w");
		fprintf(file, "255\n255\n255");
		fclose(file);
	}
	
	if (!(fileExists(timeAndBatteryFontColorPath)))
	{
		file = fopen(timeAndBatteryFontColorPath, "w");
		fprintf(file, "255\n255\n255");
		fclose(file);
	}
	
	if (!(fileExists(settingsFontColorPath)))
	{
		file = fopen(settingsFontColorPath, "w");
		fprintf(file, "0\n0\n0");
		fclose(file);
	}
}

void sleepThread(u32 milliSec) 
{
    u64 nano = milliSec * 1000000;
    svcSleepThread(nano);
}

int setFileDefaultsInt(char *path, int value, int var)
{
	FILE *temp;
	 
	if (!(fileExists(path)))
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
	 
	if (!(fileExists(path)))
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
	
	if (!(fileExists(path)))
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
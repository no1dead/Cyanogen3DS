#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "lockScreen.h"
#include "main.h"
#include "powerMenu.h"
#include "settingsMenu.h"
#include "utils.h"

#define DEFAULT_DIRECTORY "/3ds"

static char cwd[1024] = DEFAULT_DIRECTORY;

u8 *SRAM_Name;

extern bool inGame;	
extern bool VSYNC;
extern bool CPU_Running;

extern u8	frameSkip;

void utf2ascii(char* dst, u16* src)
{
	if(!src || !dst)return;
	while(*src)*(dst++)=(*(src++))&0xFF;
	*dst=0x00;
}

const char *get_filename_ext(const char *filename) 
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return "";
    return dot + 1;
}

void makeDir(const char *path)
{
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, path), 0);
}

bool fileExists(char *path) 
{
    FILE * temp = fopen(path, "r");
    if(temp == NULL)
        return false;

    fclose(temp);

    return true;
}

int loadFiles() 
{
	Handle dirHandle;
	FS_DirectoryEntry entry;

	FS_Path dirPath = fsMakePath(PATH_ASCII, cwd);
	sdmcArchive = 0;
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	FSUSER_OpenDirectory(&dirHandle, sdmcArchive, dirPath);
	
	int i = 1;
	u32 entriesRead;
	static char name[1024];

	sftd_draw_textf(robotoS12, 76, 25, RGBA8(255, 255, 255, 255), 12, "%s", cwd);
	
	for (;;)
	{
		entriesRead=0;
		FSDIR_Read(dirHandle, &entriesRead, 1, (FS_DirectoryEntry*)&entry);
		if (entriesRead)
		{
			i++;
			utf2ascii(&name[0],entry.name);
			sftd_draw_textf(robotoS12, 36, -21 + (i * 39), RGBA8(0, 0, 0, 255), 12, "%s", name);
		}
		else break;
	}
	
	FSDIR_Close(dirHandle);
	svcCloseHandle(dirHandle);
	FSUSER_CloseArchive(sdmcArchive);
	
	return 1;
}

int fileManager()
{
	sf2d_texture *fileManagerBg;
	load_PNG(fileManagerBg, "romfs:/fileManagerBg.png");
	fsInit();
	sdmcInit();
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(fileManagerBg, 0, 0);
		
		loadFiles();
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0); 
		//androidQuickSettings();
		//cursorController();
		
		sf2d_end_frame();
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(fileManagerBg);
			appDrawer();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
			appDrawer();
		
		sf2d_swapbuffers();
	}
	
	sf2d_free_texture(fileManagerBg);
	sdmcExit();
	fsExit();

	return 0;
}
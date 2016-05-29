#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "lockScreen.h"
#include "main.h"
#include "powerMenu.h"

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

void makeDir(const char *path)
{
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, path), 0);
}

bool fileExists(char* path, FS_Archive* archive)
{
	if(!path || !archive)return false;

	Result ret;
	Handle fileHandle;

	ret=FSUSER_OpenFile(&fileHandle, *archive, fsMakePath(PATH_ASCII, path), FS_OPEN_READ, 0);
	if(ret!=0)return false;

	ret=FSFILE_Close(fileHandle);
	if(ret!=0)return false;

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

void updateCurrentFile()
{
	u32 kDown = hidKeysDown();
	
	if(fileSystem.inMenu == 0) 
	{
		if(kDown & KEY_DUP)
		{
			if(!fileSystem.UKEY_UP)
			{
				if(fileSystem.sFile > 0) 
					fileSystem.sFile--;
				else 
				{
					if(fileSystem.cFile > 0)
					   fileSystem.cFile--;
				}

				if(fileSystem.currFile > 0)
					fileSystem.currFile--;
				
				fileSystem.UKEY_UP = 1;
			}
		}
		else 
		{
			fileSystem.UKEY_UP = 0;
		}

		if(kDown & KEY_DDOWN)
		{
			if(!fileSystem.UKEY_DOWN) 
			{
				if(fileSystem.cFile < fileSystem.totalFiles)
					fileSystem.cFile++;
				 else 
					fileSystem.sFile++;
				
				fileSystem.currFile++;
				
				fileSystem.UKEY_DOWN = 1;
			}
		} 
		else 
		{
			fileSystem.UKEY_DOWN = 0;
		}


		if(kDown & KEY_DLEFT) 
		{
			if(!fileSystem.UKEY_LEFT) 
			{
				fileSystem.inMenu = 1;

				fileSystem.UKEY_LEFT = 1;
			}
		} 
		else
		{
			fileSystem.UKEY_LEFT = 0;
		}
	

	}


	if(kDown & KEY_B) 
	{
		if(!fileSystem.UKEY_B) 
		{
			fileSystem.UKEY_B = 1;
		} 
			else 
		{
			fileSystem.UKEY_B = 0;
		}
	}

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
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(fileManagerBg, 0, 0);
		
		loadFiles();
		updateCurrentFile();
		
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
		
		sf2d_swapbuffers();
	}
	
	sf2d_free_texture(fileManagerBg);
	sdmcExit();
	fsExit();

	return 0;
}
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

void unicodeToChar(char* dst, u16* src, int max)
{
	if(!src || !dst)
		return;
	int n=0;
	while(*src && n<max-1){*(dst++)=(*(src++))&0xFF;n++;}
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

void loadFiles() 
{
	Handle dirHandle;
	static char fullPath[1024];
	
	static FS_DirectoryEntry dirStruct;
	memset(&dirStruct,0,sizeof(FS_DirectoryEntry));
	FS_Path dirPath = fsMakePath(PATH_ASCII, cwd);

	// init SDMC archive
	sdmcArchive=(FS_Archive){0x00000009, (FS_Path){PATH_EMPTY, 1, (u8*)""}};
	FSUSER_OpenArchive(&sdmcArchive);
	FSUSER_OpenDirectory(&dirHandle, sdmcArchive, dirPath);

	// Get number of files in directory
	fileSystem.totalFiles = 0;
	while(1) 
	{
		u32 dataRead = 0;
		FSDIR_Read(dirHandle, &dataRead, 1, &dirStruct);
		if(dataRead == 0) 
			break;
		fileSystem.totalFiles++;
	}

	fileSystem.fileList = linearAlloc(MAX_FILENAME_SIZE * fileSystem.totalFiles);

	FSUSER_OpenDirectory(&dirHandle, sdmcArchive, dirPath);

	fileSystem.totalFiles = 0;
	
	strncpy(fullPath, cwd, 1024);
	int n = strlen(fullPath);
	while(1) 
	{
		u32 dataRead = 0;
		FSDIR_Read(dirHandle, &dataRead, 1, &dirStruct);
		if(dataRead == 0) 
			break;
		unicodeToChar(&fullPath[n], dirStruct.name, 1024-n);
		fileSystem.totalFiles++;
	}

	FSDIR_Close(dirHandle);
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

void drawFiles() 
{
	int i = 0;

	for(i = 0; i < fileSystem.totalFiles; i++) 
	{
		sftd_draw_textf(robotoS12, (240 / 2), 55 + (i * 15), RGBA8(0, 0, 0, 255), 12, "%s", fileSystem.fileList[i * MAX_FILENAME_SIZE]);
	}

	sftd_draw_textf(robotoS12, 10, (fileSystem.cFile * 15) + 53, RGBA8(0, 0, 0, 255), 12, "->");

}

int fileManager()
{
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
		drawFiles();
		updateCurrentFile();
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0); 
		//androidQuickSettings();
		cursorController();
		
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
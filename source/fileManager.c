#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "lockScreen.h"
#include "main.h"
#include "powerMenu.h"
#include "settingsMenu.h"
#include "utils.h"

static char cwd[1024] = DEFAULT_DIRECTORY;
char fileNames[MAX_DISPLAY][512];

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

int makeDir(const char *path)
{
	if (!path) 
		return -1;
	
	return mkdir(path, 0777);
}

bool fileExists(char *path) 
{
    FILE * temp = fopen(path, "r");
    if(temp == NULL)
        return false;

    fclose(temp);

    return true;
}

bool dirExists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

void dirUp()
{
	current--; // Subtract a value from current so the ">" goes up
	if ((current <= curScroll-1) && (curScroll > 1)) 
	{
		curScroll--; // To do with how it scrolls
	}
}

void dirDown()
{
	if (fileNames[current+1]) 
		current++; // Add a value onto current so the ">" goes down
	if (current >= (MAX_DISPLAY + curScroll)) 
	{
		curScroll++; // To do with how it scrolls
	}
}

void dirUpx5()
{
	current -= 5;  // Subtract a value from current so the ">" goes up
	if ((current <= curScroll-1) && (curScroll > 1)) 
	{
		curScroll -= 5;  // To do with how it scrolls
	}
}

void dirDownx5()
{
	if (fileNames[current+1]) 
		current += 5; // Add a value onto current so the ">" goes down
	if (current >= (MAX_DISPLAY + curScroll)) 
	{
		curScroll += 5; // To do with how it scrolls
	}
}

int loadFiles() 
{
	Handle dirHandle;
	FS_DirectoryEntry entry;

	FS_Path dirPath = fsMakePath(PATH_ASCII, cwd);
	sdmcArchive = 0;
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	FSUSER_OpenDirectory(&dirHandle, sdmcArchive, dirPath);
	
	u32 entriesRead;
	//static char name[1024];
	//int current = 0;

	sftd_draw_textf(robotoS12, 76, 25, RGBA8(255, 255, 255, 255), 12, "%s", cwd);
	
	sf2d_draw_texture(bar , 0, 6 + (current - curScroll) * 39);
	
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (current <= curScroll - 1) 
		{
			current = curScroll;
			break;
		}
		
		entriesRead = 0;
		FSDIR_Read(dirHandle, &entriesRead, 1, (FS_DirectoryEntry*)&entry);
		
		if (entriesRead)
		{
			i++;
			utf2ascii(fileNames[i], entry.name);
			sftd_draw_textf(robotoS12, 36, (i - curScroll) * 19 + DISPLAY_Y, RGBA8(0, 0, 0, 255), 12, "%s", fileNames[i]);
		}
		else
			break;
	}
	
	kDown = hidKeysDown();
	
	if (kDown & KEY_DOWN) 
	{
		dirDown();
	}
	else if (kDown & KEY_UP) 
	{
		dirUp();
	}	
	
	if (current < 1) 
		current = 1;
	if (current > MAX_FILES) 
		current = MAX_FILES;
	
	FSDIR_Close(dirHandle);
	svcCloseHandle(dirHandle);
	FSUSER_CloseArchive(sdmcArchive);
	
	return 1;
}

int fileManager()
{	
	load_PNG(fileManagerBg, "romfs:/fileManagerBg.png");
	load_PNG(bar, "romfs:/bar.png");
	
	setBilinearFilter(1, fileManagerBg);
	setBilinearFilter(1, fileManagerBg);
	
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
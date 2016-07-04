#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "lockScreen.h"
#include "main.h"
#include "powerMenu.h"
#include "settingsMenu.h"
#include "screenshot.h"
#include "utils.h"

static char cwd[1024] = DEFAULT_DIRECTORY;
char fileNames[MAX_DISPLAY][512];

u8 *SRAM_Name;

extern bool inGame;	
extern bool VSYNC;
extern bool CPU_Running;

extern u8	frameSkip;

void openSdArchive()
{
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
}

void closeSdArchive()
{
	FSUSER_CloseArchive(sdmcArchive);
}

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

bool deleteFile(const char *path) 
{
	openSdArchive();
	Result ret = FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, path));
	closeSdArchive();
	return ret == 0;
}

Handle openDirectory(const char *path) 
{
	Handle dir;

	FS_Path filePath = fsMakePath(PATH_ASCII, path);
	if(R_FAILED(FSUSER_OpenDirectory(&dir, sdmcArchive, filePath))) 
	{
		return 0;
	}
	
	return(dir);
}

void dirUp()
{
	current-=1; // Subtract a value from current so the ">" goes up
	if ((current <= curScroll-1) && (curScroll > 1)) 
	{
		curScroll-=1; // To do with how it scrolls
	}
}

void dirDown()
{
	if (fileNames[current+1]) 
		current+=1; // Add a value onto current so the ">" goes down
	if (current >= (MAX_DISPLAY + curScroll)) 
	{
		curScroll+=1; // To do with how it scrolls
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

int loadFiles(const char * path)
{
	Handle dirHandle;
	FS_DirectoryEntry entry;

	FS_Path dirPath = fsMakePath(PATH_ASCII, path);
	sdmcArchive = 0;
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	FSUSER_OpenDirectory(&dirHandle, sdmcArchive, dirPath);
	
	u32 entriesRead;
	//static char name[1024];
	//int current = 0;
	
	sf2d_draw_texture(bar, 0, 6 + (current - curScroll) * 39);
	
	int i = 0;
	
	for (i = 0; i < MAX_FILES; i++)
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
			sftd_draw_textf(robotoS12, 76, (i - curScroll) * 19 + DISPLAY_Y, RGBA8(0, 0, 0, 255), 12, "%s", fileNames[i]);
		}
		else
			break;
		
		const char * ext = get_filename_ext(fileNames[i]);
		
		if(entry.attributes & FS_ATTRIBUTE_DIRECTORY)
			sf2d_draw_texture(dirIcon, 31, (i - curScroll) * 19 + ICON_DISPLAY_Y);
		else if(((ext) != NULL) && (((strcmp(ext ,"smdh") == 0)) || ((strcmp(ext ,"SMDH") == 0))))
			sf2d_draw_texture(fileIcon, 31, (i - curScroll) * 19 + ICON_DISPLAY_Y);
		else if(((ext) != NULL) && (((strcmp(ext ,"3dsx") == 0)) || ((strcmp(ext ,"3DSX") == 0))))
			sf2d_draw_texture(appIcon, 31, (i - curScroll) * 19 + ICON_DISPLAY_Y);
		else
			sf2d_draw_texture(fileIcon, 31, (i - curScroll) * 19 + ICON_DISPLAY_Y);
	}
	
	sf2d_draw_texture_part(fileManagerBg, 0, 0, 0, 0, 400, 46);
	sftd_draw_textf(robotoS12, 76, 25, RGBA8(255, 255, 255, 255), 12, "%s", path);
	
	//kDown = hidKeysDown();
	
	if (kDown & KEY_DOWN) 
	{
		dirDown();
	}
	else if (kDown & KEY_UP) 
	{
		dirUp();
	}	
	
	if((entry.attributes & FS_ATTRIBUTE_DIRECTORY) && (kDown & KEY_A)) 
	{
		openDirectory(fileNames[i]);
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
	load_PNG(dirIcon, "romfs:/ic_fso_folder.png");
	load_PNG(appIcon, "romfs:/ic_fso_type_app.png");
	load_PNG(fileIcon, "romfs:/ic_fso_default.png");
	
	setBilinearFilter(1, fileManagerBg);
	setBilinearFilter(1, bar);
	setBilinearFilter(1, dirIcon);
	setBilinearFilter(1, appIcon);
	setBilinearFilter(1, fileIcon);
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(fileManagerBg, 0, 0);
		
		loadFiles(cwd);
		
		if (screenDisplay == 0)
		{
			digitalTime(343, 2);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
		}
		
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
	
		captureScreenshot();
		
		sf2d_swapbuffers();
	}
	
	sf2d_free_texture(fileManagerBg);

	return 0;
}
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

struct fileManagerFontColor fmFontColor;

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

void unicodeToChar(char* dst, u16* src, int max)
{
	if(!src || !dst)return;
	int n=0;
	while(*src && n<max-1){*(dst++)=(*(src++))&0xFF;n++;}
	*dst=0x00;
}

Handle openFileHandle(const char * path) 
{
    Handle fileHandle = 0;
	
    FS_Path filePath = fsMakePath(PATH_ASCII, path);
	
	//openSdArchive();
	
    if (FSUSER_OpenFile(&fileHandle, ARCHIVE_SDMC, filePath, FS_OPEN_READ & 3, 0)) 
	{
        FSUSER_OpenFile(&fileHandle, ARCHIVE_SDMC, filePath, FS_OPEN_READ, 0);
    }
	
	//closeSdArchive();
	
    return fileHandle;
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
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	FSUSER_OpenDirectory(&dirHandle, sdmcArchive, dirPath);
	
	u32 entriesRead;
	//static char name[1024];
	//int current = 0;

	sftd_draw_textf(robotoS12, 76, 25, RGBA8(255, 255, 255, 255), 12, "%s", path);
	
	sf2d_draw_texture(bar, 0, 6 + (current - curScroll) * 39);
	
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
			sftd_draw_textf(robotoS12, 76, (i - curScroll) * 19 + DISPLAY_Y, RGBA8(fmFontColor.r, fmFontColor.g, fmFontColor.b, 255), 12, "%s", fileNames[i]);
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
	
	captureScreenshot();
	
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
	FILE *temp;
	 
	if (!(fileExists(fileManagerFontColorPath)))
	{
		temp = fopen(fileManagerFontColorPath, "w");
		fprintf(temp, "0\n0\n0");
		fclose(temp);
	}
	
	temp = fopen(fileManagerFontColorPath, "r");
	fscanf(temp, "%d %d %d", &fmFontColor.r, &fmFontColor.g, &fmFontColor.b);
	fclose(temp);
	

	load_PNG(fileManagerBg, fmBgPath);
	load_PNG(bar, fmSelectorPath);
	load_PNG(dirIcon, diriconPath);
	load_PNG(appIcon, "/3ds/Cyanogen3DS/system/app/filemanager/ic_fso_type_app.png");
	load_PNG(fileIcon, "/3ds/Cyanogen3DS/system/app/filemanager/ic_fso_default.png");
	
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
			digitalTime(343, 2, 0);
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
			sf2d_free_texture(bar);
			sf2d_free_texture(dirIcon);
			sf2d_free_texture(appIcon);
			sf2d_free_texture(fileIcon);
			appDrawer();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
			appDrawer();
		
		sf2d_swapbuffers();
	}
	
	sf2d_free_texture(fileManagerBg);
	sf2d_free_texture(bar);
	sf2d_free_texture(dirIcon);
	sf2d_free_texture(appIcon);
	sf2d_free_texture(fileIcon);

	return 0;
}
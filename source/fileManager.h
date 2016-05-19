#pragma once

#include <3ds.h>
#include <stdbool.h>

#define MAX_FILENAME_SIZE 0xA0

sf2d_texture *fileManagerBg;

FS_Archive sdmcArchive;

typedef struct FS_MAIN 
{
	u8 UKEY_UP;
	u8 UKEY_DOWN;
	u8 UKEY_LEFT;
	u8 UKEY_RIGHT;
	u8 UKEY_B;

	// Selected File
	int sFile; 
	// Cursor File 
	int cFile; 
	// Current File 
	int currFile;
	// inConfiguration 
	bool inMenu;
	// Configuration Menu Cursor
	int cConfig;
	// FileList 
	char *fileList;
	// totalFiles 
	int totalFiles;
} FS_MAIN;


FS_MAIN fileSystem;

void unicodeToChar(char* dst, u16* src, int max);
void makeDir(const char *path);
bool fileExists(char* path, FS_Archive* archive);
void loadFiles();
void updateCurrentFile();
void drawFiles();
int fileManager();
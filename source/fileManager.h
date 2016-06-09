#pragma once

#include <3ds.h>
#include <stdbool.h>
#include <sys/stat.h>

#define MAX_FILENAME_SIZE 0xA0

FS_Archive sdmcArchive;

void utf2ascii(char* dst, u16* src);
const char *get_filename_ext(const char *filename);
int makeDir(const char *path);
bool fileExists(char *path);
bool dirExists(const char *path);
int loadFiles();
int fileManager();
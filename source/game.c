#include "game.h"
#include "fileManager.h"

/*These are mostly based off of rinnegatamte's lua player plus src code. 
I will alter these to my needs later.*/

bool isNinjhax2(void)
{
	Result ret = hbInit();
	if(!ret)
	{
		hbExit();
		return false;
	}else return true;
}

extern void (*__system_retAddr)(void);

static Handle hbFileHandle;
static u32 argbuffer[0x200];
static u32 argbuffer_length = 0;

// ninjhax 1.x
void (*callBootloader_1x)(Handle hb, Handle file);
void (*setArgs_1x)(u32* src, u32 length);

static void launchFile_1x(void)
{
	// jump to bootloader
	callBootloader_1x(0x00000000, hbFileHandle);
}

// ninjhax 2.0+
typedef struct
{
	int processId;
	bool capabilities[0x10];
}processEntry_s;

void (*callBootloader_2x)(Handle file, u32* argbuf, u32 arglength) = (void*)0x00100000;
void (*callBootloaderNewProcess_2x)(int processId, u32* argbuf, u32 arglength) = (void*)0x00100008;
void (*callBootloaderRunTitle_2x)(u8 mediatype, u32* argbuf, u32 argbuflength, u32 tid_low, u32 tid_high) = (void*)0x00100010;
void (*getBestProcess_2x)(u32 sectionSizes[3], bool* requirements, int num_requirements, processEntry_s* out, int out_size, int* out_len) = (void*)0x0010000C;

int targetProcessId = -1;
titleInfo_s  target_title;

static void launchFile_2x(void)
{
	// jump to bootloader
	if(targetProcessId == -1)callBootloader_2x(hbFileHandle, argbuffer, argbuffer_length);
	else if(targetProcessId == -2)callBootloaderRunTitle_2x(target_title.mediatype, argbuffer, argbuffer_length, target_title.title_id & 0xffffffff, (target_title.title_id >> 32) & 0xffffffff);
	else callBootloaderNewProcess_2x(targetProcessId, argbuffer, argbuffer_length);
}

int launch3DSX(const char * path)
{
	if (isNinjhax2())
	{
		argbuffer[0] = 1;
		snprintf((char*)&argbuffer[1], sizeof(argbuffer) - 4, "sdmc:%s", path);
		argbuffer_length = 0x100;
	}
	else 
	{
		HB_GetBootloaderAddresses((void**)&callBootloader_1x, (void**)&setArgs_1x);
		hbExit();
	}
	
	openSdArchive();
	Result ret = FSUSER_OpenFileDirectly(&hbFileHandle, ARCHIVE_SDMC,  fsMakePath(PATH_EMPTY, ""), fsMakePath(PATH_ASCII, path), FS_OPEN_READ, 0x00000000);
		if (ret) 
			return 0;
	if (isNinjhax2()) 
		__system_retAddr = launchFile_2x;
	else
	{
		static u32 argbuffer_nh1[0x200];
		argbuffer_nh1[0]=1;
		snprintf((char*)&argbuffer_nh1[1], 0x800, "sdmc:%s", path);
		setArgs_1x(argbuffer_nh1, 0x800);
		__system_retAddr = launchFile_1x;
	}
	
	return 0;
}

int launchApp(u64 titleId) 
{
	char product_id[16];
	AM_GetTitleProductCode(MEDIATYPE_GAME_CARD, 0, product_id);
	
	//if (product_id[0] == 'C' && product_id[1] == 'T' && product_id[2] == 'R')
	//{
		u8 param[0x300];
		u8 hmac[0x20];
		//memset(buf0, 0, 0x300);
		//memset(buf1, 0, 0x20);
		APT_PrepareToDoApplicationJump(0, titleId, MEDIATYPE_GAME_CARD);
		APT_DoApplicationJump(param, sizeof(param), hmac);
	//}
	//else
	if (!(product_id[0] == 'C' && product_id[1] == 'T' && product_id[2] == 'R'))
	{
		nsInit();
		NS_RebootToTitle(MEDIATYPE_GAME_CARD,0);
		nsExit();
	}
	
	return 0;
}

char * getCardID() 
{
	static char product_id[16]; //quick/hacky fix. This shouldn't be static
	AM_GetTitleProductCode(MEDIATYPE_GAME_CARD, 0, product_id);
	if (product_id[0] == 'C' && product_id[1] == 'T' && product_id[2] == 'R') 
		return product_id;
	else 
		return NULL;
}

int installCIA(const char *path)
{
	Handle dirHandle, ciaHandle = 0;
	
	FS_Path filePath = fsMakePath(PATH_ASCII, path);
	
	Result res = FSUSER_OpenFileDirectly(&dirHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""), filePath, FS_OPEN_READ, 0x00000000);
	
	if (res != 0)
	{
		return -1;
	}

    char cia_buffer[CTR_BUFSIZE];
    memset(cia_buffer, 0, CTR_BUFSIZE);
    u64 size, bytesToRead, i = 0; u32 bytes;
	FSFILE_GetSize(dirHandle, &size);

	res = AM_StartCiaInstall(MEDIATYPE_SD, &ciaHandle);
	if (res != 0)
	{
		return -1;
	}

    while (i < size)
    {
        if	(i+CTR_BUFSIZE > size)
            bytesToRead = size - i;
        else
            bytesToRead = CTR_BUFSIZE;

        res = FSFILE_Read(dirHandle, &bytes, i, cia_buffer, bytesToRead);
        if (res != 0)
        {
            AM_CancelCIAInstall(ciaHandle);
            FSFILE_Close(dirHandle);
            return -1;
        }

        res = FSFILE_Write(ciaHandle, &bytes, i, cia_buffer, bytesToRead, 0);
        if (res != 0 && res != 0xc8e083fc)// 0xc8e083fc=ALREADY_EXISTS
        {
            AM_CancelCIAInstall(ciaHandle);
            FSFILE_Close(dirHandle);
            return -1;
        }

        i += bytesToRead;
	}

	res = AM_FinishCiaInstall(ciaHandle);
	if (res != 0)
	{
        AM_CancelCIAInstall(ciaHandle);
		return -1;
	}

	FSFILE_Close(dirHandle);
	return 0;
}

int launchCia(u64 titleID, FS_MediaType mediaType)
{
	u8 param[0x300];
	u8 hmac[0x20];
	
	memset(param, 0, sizeof(param));
	memset(hmac, 0, sizeof(hmac));
	APT_PrepareToDoApplicationJump(0, titleID, mediaType);
	APT_DoApplicationJump(param, sizeof(param), hmac);
	
	return 0;
}
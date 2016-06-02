#include "game.h"
#include "fileManager.h"

/*These are mostly based off of rinnegatamte's lua player plus src code. 
I will alter these to my needs later.*/

int startCard() 
{
	amInit();
	char product_id[16];
	AM_GetTitleProductCode(MEDIATYPE_GAME_CARD, 0, product_id);
	amExit();
	
	if (product_id[0] == 'C' && product_id[1] == 'T' && product_id[2] == 'R')
	{
		u8 buf0[0x300];
		u8 buf1[0x20];
		memset(buf0, 0, 0x300);
		memset(buf1, 0, 0x20);
		aptOpenSession();
		APT_PrepareToDoAppJump(0, 0, MEDIATYPE_GAME_CARD);
		APT_DoAppJump(0x300, 0x20, buf0, buf1);
		aptCloseSession();
	}
	else
	{
		nsInit();
		NS_RebootToTitle(MEDIATYPE_GAME_CARD,0);
		nsExit();
	}
	
	return 0;
}

char * getCardID() 
{
	amInit();
	static char product_id[16]; //quick/hacky fix. This shouldn't be static
	AM_GetTitleProductCode(MEDIATYPE_GAME_CARD, 0, product_id);
	amExit();
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

int launchCia(/*FS_MediaType mediaType, u64 titleID*/)
{
	u32 unique_id = 0;
	u32 mediatype = 0;
	u8 buf0[0x300];
	u8 buf1[0x20];
	u64 id = unique_id | ((u64)0x00040000 << 32);
	memset(buf0, 0, 0x300);
	memset(buf1, 0, 0x20);
	aptOpenSession();
	APT_PrepareToDoAppJump(0, id, mediatype);
	APT_DoAppJump(0x300, 0x20, buf0, buf1);
	aptCloseSession();
	return 0;
}
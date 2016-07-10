#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "lockScreen.h"
#include "settingsMenu.h"
#include "utils.h"

int lockScreen()
{
	char passwordData[20] = "";
	char pinData[5] = "";
	int passProtect = 0;
	
	load_PNG(lockscreenBg, "romfs:/lockscreenBg.png");
	setBilinearFilter(1, lockscreenBg);
	
	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));
	
	static SwkbdState swkbd;
	
	if (fileExists("/3ds/Cyanogen3DS/system/settings/password.bin"))
		passProtect = 1;	
	else if (fileExists("/3ds/Cyanogen3DS/system/settings/pin.bin"))
		passProtect = 2;
	else if ((!(fileExists("/3ds/Cyanogen3DS/system/settings/password.bin"))) || (!(fileExists("/3ds/Cyanogen3DS/system/settings/pin.bin"))))
		passProtect = 0;

	while (1)
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(background, 0, 0);
		sf2d_draw_texture(lockscreenBg, 0, 0);

		digitalTime(155, 30, 1);
		sftd_draw_textf(robotoS10, 150, 90, RGBA8(255, 255, 255, 255), 10, "%s", getDayOfWeek(0));
		sftd_draw_textf(robotoS10, 215, 90, RGBA8(255, 255, 255, 255), 10, "%s", getMonthOfYear(0));
		
		digitalTime(352, 2, 0);
		batteryStatus(300, 2, 0); 
		cursorController();
		
		sf2d_end_frame();
		
		
		if (passProtect == 1)
		{	
			if ((cursorX  >= 160 && cursorX  <= 235 && cursorY >= 210 && cursorY <= 240) && (kDown & KEY_A))
			{	
				FILE * password = fopen("/3ds/Cyanogen3DS/system/settings/password.bin", "r");
				fscanf(password, "%s", passwordData);
				fclose(password);
		
				swkbdInit(&swkbd, SWKBD_TYPE_WESTERN, 2, 20);
				swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
				swkbdInputText(&swkbd, tempMessage, sizeof(tempMessage));
				
				if (strcmp(tempMessage, passwordData) == 0)
				{
					sf2d_free_texture(lockscreenBg);
					return 1;
				}
				else if (strcmp(tempMessage, passwordData) != 0)
				{
					sf2d_free_texture(lockscreenBg);
					return lockScreen();
				}	
			}
		}
		
		else if (passProtect == 2)
		{			
			if ((cursorX  >= 160 && cursorX  <= 235 && cursorY >= 210 && cursorY <= 240) && (kDown & KEY_A))
			{	
				FILE * pin = fopen("/3ds/Cyanogen3DS/system/settings/pin.bin", "r");
				fscanf(pin, "%s", pinData);
				fclose(pin);
		
				swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 4);
				swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_HIDE_DELAY);
				swkbdSetValidation(&swkbd, SWKBD_ANYTHING, 0, 0);
				swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
				swkbdInputText(&swkbd, tempPin, sizeof(tempPin));
				
				if (strcmp(tempPin, pinData) == 0)
				{
					sf2d_free_texture(lockscreenBg);
					return 1;
				}
				else if (strcmp(tempPin, pinData) != 0)
				{
					sf2d_free_texture(lockscreenBg);
					return lockScreen();
				}	
			}
		}
		
		else if (passProtect == 0)
		{
			if ((cursorX  >= 160 && cursorX  <= 235 && cursorY >= 210 && cursorY <= 240) && (kDown & KEY_A))
			{	
				sf2d_free_texture(lockscreenBg);
				return 1;
			}
		}
			
		sf2d_swapbuffers();
	}
	
	sf2d_free_texture(lockscreenBg);
	
	return 0;
}
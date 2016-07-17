#include "clock.h"
#include "homeMenu.h"
#include "main.h"
#include "powerMenu.h"
#include "screenshot.h"
#include "settingsMenu.h"
#include "utils.h"

int powerMenu()
{
	load_PNG(power, "/3ds/Cyanogen3DS/system/home/menu/powerMenu.png");
	load_PNG(powerSelection, "/3ds/Cyanogen3DS/system/home/menu/powerSelection.png");
	load_PNG(recoverySelection, "/3ds/Cyanogen3DS/system/home/menu/recoverySelection.png");
	
	setBilinearFilter(1, power);
	setBilinearFilter(1, powerSelection);
	setBilinearFilter(1, recoverySelection);

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();

		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		sf2d_draw_texture(background, 0, 0);
		
		if (screenDisplay == 0)
		{
			sf2d_draw_texture(ic_launcher_browser, 49, 155);
			sf2d_draw_texture(ic_launcher_messenger, 114, 155);
			sf2d_draw_texture(ic_launcher_apollo, 241, 155);
			sf2d_draw_texture(ic_launcher_settings, 306, 155);
	
			appDrawerIcon(screenDisplay);
			
			sf2d_draw_texture(power, 62, 50);

			sftd_draw_textf(robotoS18, 140, 80, RGBA8(0, 0, 0, 255), 18, "Power Off");
			sftd_draw_textf(robotoS18, 140, 144, RGBA8(0, 0, 0, 255), 18, "Recovery");
		}
		
		else if (screenDisplay == 1)
		{
			sf2d_draw_texture(ic_launcher_browser, 9, 140);
			sf2d_draw_texture(ic_launcher_messenger, 74, 140);
			sf2d_draw_texture(ic_launcher_apollo, 201, 140);
			sf2d_draw_texture(ic_launcher_settings, 266, 140);
	
			appDrawerIcon(screenDisplay);
			
			sf2d_draw_texture_scale(power, 42, 50, 0.9, 0.9);

			sftd_draw_textf(robotoS18, 120, 80, RGBA8(0, 0, 0, 255), 16, "Power Off");
			sftd_draw_textf(robotoS18, 140, 144, RGBA8(0, 0, 0, 255), 18, "Recovery");
		}

		if (cursor(52, 340, 40, 116))
		{
			if (screenDisplay == 1)
			{
				sf2d_draw_texture_scale(powerSelection, 42, 49, 0.9, 0.9);
				sftd_draw_textf(robotoS18, 120, 80, RGBA8(0, 0, 0, 255), 16, "Power Off");
				sftd_draw_textf(robotoS18, 140, 144, RGBA8(0, 0, 0, 255), 18, "Recovery");
			}
			else
			{
				sf2d_draw_texture(powerSelection, 62, 49);
				sftd_draw_textf(robotoS18, 140, 80, RGBA8(0, 0, 0, 255), 18, "Power Off");
				sftd_draw_textf(robotoS18, 140, 144, RGBA8(0, 0, 0, 255), 18, "Recovery");
			}
			if (kDown & KEY_A)
			{
				longjmp(exitJmp, 1);
			}
		}
		else if (cursor(52, 340, 118, 180))
		{
			if (screenDisplay == 1)
			{
				sf2d_draw_texture_scale(recoverySelection, 42, 49, 0.9, 0.9);
				sftd_draw_textf(robotoS18, 120, 80, RGBA8(0, 0, 0, 255), 16, "Power Off");
				sftd_draw_textf(robotoS18, 140, 144, RGBA8(0, 0, 0, 255), 18, "Recovery");
			}
			else
			{
				sf2d_draw_texture(recoverySelection, 62, 49);
				sftd_draw_textf(robotoS18, 140, 80, RGBA8(0, 0, 0, 255), 18, "Power Off");
				sftd_draw_textf(robotoS18, 140, 144, RGBA8(0, 0, 0, 255), 18, "Recovery");
			}
			if (kDown & KEY_A)
			{
				longjmp(exitJmp, 1);
			}
		}
		
		if (screenDisplay == 0)
		{
			digitalTime(352, 2, 0);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
		}
		
		cursorController();

		sf2d_end_frame();
		
		navbarControls(0);

		if (kDown & KEY_B)
			break;

		captureScreenshot();
		
		sf2d_swapbuffers();
	}

	sf2d_free_texture(power);
	sf2d_free_texture(powerSelection);
	sf2d_free_texture(recoverySelection);
	
	return 0;
}
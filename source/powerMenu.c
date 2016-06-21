#include "clock.h"
#include "homeMenu.h"
#include "main.h"
#include "powerMenu.h"
#include "settingsMenu.h"
#include "utils.h"

int powerMenu()
{
	load_PNG(power, "romfs:/powerMenu.png");
	load_PNG(power1, "romfs:/powerSelection.png");
	
	setBilinearFilter(1, power);
	setBilinearFilter(1, power1);

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
			
			sf2d_draw_texture(power, 62, 100);

			sftd_draw_textf(robotoS18, 140, 118, RGBA8(0, 0, 0, 255), 18, "Power Off");
		}
		
		else if (screenDisplay == 1)
		{
			sf2d_draw_texture(ic_launcher_browser, 9, 140);
			sf2d_draw_texture(ic_launcher_messenger, 74, 140);
			sf2d_draw_texture(ic_launcher_apollo, 201, 140);
			sf2d_draw_texture(ic_launcher_settings, 266, 140);
	
			appDrawerIcon(screenDisplay);
			
			sf2d_draw_texture_scale(power, 42, 100, 0.9, 0.9);

			sftd_draw_textf(robotoS18, 120, 118, RGBA8(0, 0, 0, 255), 16, "Power Off");
		}

		if (cursor(62, 338, 80, 159))
		{
			if (screenDisplay == 1)
			{
				sf2d_draw_texture_scale(power1, 42, 100, 0.9, 0.9);
				sftd_draw_textf(robotoS18, 120, 118, RGBA8(0, 0, 0, 255), 16, "Power Off");
			}
			else
			{
				sf2d_draw_texture(power1, 62, 100);
				sftd_draw_textf(robotoS18, 140, 118, RGBA8(0, 0, 0, 255), 18, "Power Off");
			}
			if (kDown & KEY_A)
			{
				longjmp(exitJmp, 1);
			}
		}

		if (screenDisplay == 0)
		{
			digitalTime(343, 2);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
		}
		
		cursorController();

		sf2d_end_frame();
		
		navbarControls(0);

		if (kDown & KEY_B)
			break;

		sf2d_swapbuffers();
	}

	sf2d_free_texture(power);
	sf2d_free_texture(power1);
	
	return 0;
}
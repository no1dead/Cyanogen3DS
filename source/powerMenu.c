#include "clock.h"
#include "homeMenu.h"
#include "powerMenu.h"
#include "main.h"

int powerMenu()
{
	load_PNG(power, "romfs:/powerMenu.png");
	load_PNG(power1, "romfs:/powerSelection.png");
	
	robotoPowerMenu = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size); //Loads font

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(background, 0, 0);
		sf2d_draw_texture(ic_launcher_browser, 49, 155);
		sf2d_draw_texture(ic_launcher_messenger, 114, 155);
		sf2d_draw_texture(ic_launcher_apollo, 241, 155);
		sf2d_draw_texture(ic_launcher_settings, 306, 155);
			
		appDrawerIcon();
		dayNightWidget();
			
		sf2d_draw_texture(power, 62, 100);

		sftd_draw_textf(robotoPowerMenu, 140, 118, RGBA8(0, 0, 0, 255), 18, "Power Off");

		if (cursor(62, 338, 80, 159))
		{
			sf2d_draw_texture(power1, 62, 100);
			sftd_draw_textf(robotoPowerMenu, 140, 118, RGBA8(0, 0, 0, 255), 18, "Power Off");
			if (kDown & KEY_A)
			{
				longjmp(exitJmp, 1);
			}
		}

		digitalTime(350, 2); 
		batteryStatus(300, 2);
		cursorController();

		sf2d_end_frame();
		
		navbarControls(0);

		if (kDown & KEY_B)
			break;

		sf2d_swapbuffers();
	}

	sftd_free_font(robotoPowerMenu);
	sf2d_free_texture(power);
	sf2d_free_texture(power1);
	
	return 0;
}

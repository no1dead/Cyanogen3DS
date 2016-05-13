#include "appDrawer.h"
#include "clock.h"
#include "homeMenu.h"
#include "language.h"
#include "lockScreen.h"
#include "powerMenu.h"
#include "settingsMenu.h"

void appDrawerUnload()
{
	sf2d_free_texture(backdrop);
	sf2d_free_texture(ic_launcher_clock);
	sf2d_free_texture(ic_launcher_filemanager);
	sf2d_free_texture(ic_launcher_gallery);
	sf2d_free_texture(ic_launcher_game);
}

int appDrawer()
{	

	load_PNG(backdrop, "romfs:/backdrop.png");
	load_PNG(ic_launcher_clock, "romfs:/ic_launcher_clock.png");
	load_PNG(ic_launcher_filemanager, "romfs:/ic_launcher_filemanager.png");
	load_PNG(ic_launcher_gallery, "romfs:/ic_launcher_gallery.png");
	load_PNG(ic_launcher_game, "romfs:/ic_launcher_game.png");

	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));
	
	while (aptMainLoop())
	{	
		hidScanInput();
		
		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(background, 0, 0);
		sf2d_draw_texture(backdrop, 0, 24);

		sf2d_draw_texture(ic_launcher_browser, 20, 45);
		sftd_draw_textf(roboto, 18, 100, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][0]);
		sf2d_draw_texture(ic_launcher_clock, 95, 45);
		sftd_draw_textf(roboto, 98, 100, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][1]);
		sf2d_draw_texture(ic_launcher_filemanager, 170, 45);
		sftd_draw_textf(roboto, 167, 100, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][2]);
		sf2d_draw_texture(ic_launcher_gallery, 245, 45);
		sftd_draw_textf(roboto, 247, 100, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][3]);
		sf2d_draw_texture(ic_launcher_game, 320, 45);
		sftd_draw_textf(roboto, 325, 100, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][4]);
		sf2d_draw_texture(ic_launcher_messenger, 20, 125);
		sftd_draw_textf(roboto, 16, 180, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][5]);
		sf2d_draw_texture(ic_launcher_apollo, 95, 125);
		sftd_draw_textf(roboto, 98, 180, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][6]);
		sf2d_draw_texture(ic_launcher_settings, 170, 125);
		sftd_draw_textf(roboto, 167, 180, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][7]);
		
		digitalTime(343, 2);
		batteryStatus(300, 2);
		//androidQuickSettings();		
		cursorController();
		
		sf2d_end_frame();
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if ((cursor(170, 215, 125, 170)) && (kDown & KEY_A))
		{
			appDrawerUnload();
			settingsMenu();
		}
		
		if (kDown & KEY_B)
		{
			appDrawerUnload();
			home(); //Returns to home screen
		}
		
		sf2d_swapbuffers();	
	}
	
	appDrawerUnload();
	
	return 0;
}

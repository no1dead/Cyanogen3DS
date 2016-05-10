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
		sf2d_draw_texture(backdrop, 0, 14);

		sf2d_draw_texture(ic_launcher_browser, 20, 35);
		sftd_draw_textf(roboto, 18, 90, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][0]);
		sf2d_draw_texture(ic_launcher_clock, 95, 35);
		sftd_draw_textf(roboto, 98, 90, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][1]);
		sf2d_draw_texture(ic_launcher_filemanager, 170, 35);
		sftd_draw_textf(roboto, 167, 90, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][2]);
		sf2d_draw_texture(ic_launcher_gallery, 245, 35);
		sftd_draw_textf(roboto, 247, 90, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][3]);
		sf2d_draw_texture(ic_launcher_game, 320, 35);
		sftd_draw_textf(roboto, 325, 90, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][4]);
		sf2d_draw_texture(ic_launcher_messenger, 20, 115);
		sftd_draw_textf(roboto, 16, 170, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][5]);
		sf2d_draw_texture(ic_launcher_apollo, 95, 115);
		sftd_draw_textf(roboto, 98, 170, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][6]);
		sf2d_draw_texture(ic_launcher_settings, 170, 115);
		sftd_draw_textf(roboto, 167, 170, RGBA8(0, 0, 0, 255), 12, "%s", lang_appDrawer[language][7]);
		
		navbarControls(0);
		digitalTime(350, 2); 
		batteryStatus(300, 2);
		//androidQuickSettings();		
		cursorController();
		
		sf2d_end_frame();
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if ((cursorX  >= 170 && cursorX  <= 215 && cursorY >= 115 && cursorY <= 160) && (kDown & KEY_A))
		{
			appDrawerUnload();
			settingsMenu();
		}
		
		//Navbar controls
		if ((cursorX  >= 84 && cursorX  <= 159 && cursorY >= 201 && cursorY <= 240) && (kDown & KEY_A))
		{
			appDrawerUnload();
			home(); // Pressing the back icon - takes you back to the homescreen
		}
		
		//Navbar controls
		else if ((cursorX  >= 160 && cursorX  <= 235 && cursorY >= 201 && cursorY <= 240) && (kDown & KEY_A))
		{
			appDrawerUnload();
			home(); // Pressing the home icon always returns to the home screen
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

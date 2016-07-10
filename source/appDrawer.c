#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "game.h"
#include "homeMenu.h"
#include "language.h"
#include "lockScreen.h"
#include "powerMenu.h"
#include "screenshot.h"
#include "settingsMenu.h"
#include "utils.h"

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
	if (DARK == 1)
	{
		load_PNG(backdrop, "romfs:/Dark/backdropDark.png");
		fontColor = WHITE;
	}
	else
	{
		load_PNG(backdrop, "romfs:/backdrop.png");
		fontColor = BLACK;
	}
	
	load_PNG(ic_launcher_clock, clockPath);
	load_PNG(ic_launcher_filemanager, fmPath);
	load_PNG(ic_launcher_gallery, galleryPath);
	load_PNG(ic_launcher_game, gamePath);
	
	setBilinearFilter(1, ic_launcher_clock);
	setBilinearFilter(1,ic_launcher_filemanager);
	setBilinearFilter(1, ic_launcher_gallery);
	setBilinearFilter(1, ic_launcher_game);
	
	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));
	
	while (aptMainLoop())
	{	
		hidScanInput();
		
		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(background, 0, 0);
		
		if (screenDisplay == 1)
			sf2d_draw_texture_scale(backdrop, 0, 24, 0.8, 1.0);
		else 
			sf2d_draw_texture(backdrop, 0, 24);
		
		if (cursor(20, 65, 45, 90))
			sf2d_draw_texture_scale(ic_launcher_browser, 20, 40, 1.1, 1.1);
		else
			sf2d_draw_texture(ic_launcher_browser, 25, 45);
		sftd_draw_textf(robotoS12, 23, 100, fontColor, 12, "%s", lang_appDrawer[language][0]);
		
		if (cursor(95, 140, 45, 90))
			sf2d_draw_texture_scale(ic_launcher_clock, 95, 40, 1.1, 1.1);
		else 
			sf2d_draw_texture(ic_launcher_clock, 100, 45);
		sftd_draw_textf(robotoS12, 103, 100, fontColor, 12, "%s", lang_appDrawer[language][1]);
		
		if (cursor(170, 215, 45, 90))
			sf2d_draw_texture_scale(ic_launcher_filemanager, 170, 40, 1.1, 1.1);
		else
			sf2d_draw_texture(ic_launcher_filemanager, 175, 45);
		sftd_draw_textf(robotoS12, 172, 100, fontColor, 12, "%s", lang_appDrawer[language][2]);
		
		if (cursor(245, 290, 45, 90))
			sf2d_draw_texture_scale(ic_launcher_gallery, 245, 40, 1.1, 1.1);
		else 
			sf2d_draw_texture(ic_launcher_gallery, 250, 45);
		sftd_draw_textf(robotoS12, 252, 100, fontColor, 12, "%s", lang_appDrawer[language][3]);
		
		if (screenDisplay == 0)
		{
			if (cursor(320, 365, 45, 90))
				sf2d_draw_texture_scale(ic_launcher_game, 320, 40, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_game, 325, 45);
			sftd_draw_textf(robotoS12, 330, 100, fontColor, 12, "%s", lang_appDrawer[language][4]);
			
			if (cursor(20, 65, 125, 170))
				sf2d_draw_texture_scale(ic_launcher_messenger, 20, 120, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_messenger, 25, 125);
			sftd_draw_textf(robotoS12, 21, 180, fontColor, 12, "%s", lang_appDrawer[language][5]);
		
			if (cursor(95, 140, 125, 170))
				sf2d_draw_texture_scale(ic_launcher_apollo, 95, 120, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_apollo, 100, 125);
			sftd_draw_textf(robotoS12, 103, 180, fontColor, 12, "%s", lang_appDrawer[language][6]);
		
			if (cursor(170, 215, 125, 170))
				sf2d_draw_texture_scale(ic_launcher_settings, 170, 120, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_settings, 175, 125);
			sftd_draw_textf(robotoS12, 172, 180, fontColor, 12, "%s", lang_appDrawer[language][7]);
			
			digitalTime(352, 2, 0);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
		}
		
		else if (screenDisplay == 1)
		{
			if (cursor(20, 65, 125, 170))
				sf2d_draw_texture_scale(ic_launcher_game, 20, 120, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_game, 25, 125);
			sftd_draw_textf(robotoS12, 26, 180, fontColor, 12, "%s", lang_appDrawer[language][4]);
			
			if (cursor(95, 140, 125, 170))
				sf2d_draw_texture_scale(ic_launcher_messenger, 95, 120, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_messenger, 100, 125);
			sftd_draw_textf(robotoS12, 90, 180, fontColor, 12, "%s", lang_appDrawer[language][5]);
		
			if (cursor(170, 215, 125, 170))
				sf2d_draw_texture_scale(ic_launcher_apollo, 170, 120, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_apollo, 175, 125);
			sftd_draw_textf(robotoS12, 180, 180, fontColor, 12, "%s", lang_appDrawer[language][6]);
		
			if (cursor(245, 290, 125, 170))
				sf2d_draw_texture_scale(ic_launcher_settings, 245, 120, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_settings, 250, 125);
			sftd_draw_textf(robotoS12, 250, 180, fontColor, 12, "%s", lang_appDrawer[language][7]);
		}
		
		cursorController();
		
		sf2d_end_frame();
		
		switchDisplayModeOn(1);
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if ((cursor(170, 215, 45, 90)) && (kDown & KEY_A))
		{
			if (experimentalF == 1)
			{
				appDrawerUnload();
				fileManager();
			}		
		}
		
		/*else if ((cursor(320, 365, 45, 90)) && (kDown & KEY_A))
		{
			if (experimentalF == 1)
			{
				appDrawerUnload();
				startCard();
			}		
		}*/
		
		else if ((cursor(170, 215, 125, 170)) && (kDown & KEY_A))
		{
			appDrawerUnload();
			settingsMenu();
		}
		
		if (kDown & KEY_B)
		{
			appDrawerUnload();
			home(); //Returns to home screen
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
			home();
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}
	
	appDrawerUnload();
	
	return 0;
}

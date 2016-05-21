#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "language.h"
#include "lockScreen.h"
#include "main.h"
#include "powerMenu.h"
#include "settingsMenu.h"
#include "utils.h"


int aboutMenu()
{
	load_PNG(aboutBg, "romfs:/aboutBg.png");
	load_PNG(highlight, "romfs:/highlight.png");
	
	/*u32 firmware = osGetFirmVersion();
	u32 major = GET_VERSION_MAJOR(firmware);
	u32 minor = GET_VERSION_MINOR(firmware);
	u32 rev = GET_VERSION_REVISION(firmware);*/
	
	u8 model = getModel();
	u8 region = getRegion();
	
	char * modelName;
	char * regionName;
	
	switch (region) 
	{
		case 0: 
			regionName = "JPN"; 
			break;
		case 1: 
			regionName = "NTSC"; 
			break;
		case 2:
			regionName = "EUR"; 
			break; 
		case 3: 
			regionName = "PAL";
			break; 
		case 4: 
			regionName = "CHN"; 
			break;
		case 5: 
			regionName = "KOR";
			break;
		case 6: 
			regionName = "TWN"; 
			break;
		default: 
			regionName = "UNKNOWN";
	}

	switch (model) 
	{
		case 0: 
			modelName = "O3DS"; 
			break;
		case 1: 
			modelName = "O3DS XL"; 
			break;
		case 2: 
			modelName = "N3DS"; 
			break;
		case 3: 
			modelName = "2DS"; 
			break;
		case 4: 
			modelName = "N3DS XL"; 
			break;
		default: 
			modelName = "UNKNOWN";
	}

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);

			sf2d_draw_texture(aboutBg, 0, 0);

			sftd_draw_textf(robotoS12, 20, 68, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsAbout[language][0]);
			sftd_draw_textf(robotoS12, 20, 83, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsAbout[language][1]);
			sftd_draw_textf(robotoS12, 20, 116, RGBA8(0, 0, 0, 255), 12, "%s %s -%d%02d%02d- %s", lang_settingsAbout[language][2], VERSION, YEAR, MONTH + 1, DAY, lang_settingsAbout[language][3]);
			//sftd_draw_textf(robotoS12, 20, 132, RGBA8(0, 0, 0, 255), 12, "System Version: %s.%s.%s", major, minor, rev);
			sftd_draw_textf(robotoS12, 20, 168, RGBA8(0, 0, 0, 255), 12, "Model: %s %s", modelName, regionName);

			if (cursor(0, 480, 58, 105))
			{
				sf2d_draw_texture(highlight, 0, 56);
				sftd_draw_textf(robotoS12, 20, 68, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsAbout[language][0]);
				sftd_draw_textf(robotoS12, 20, 83, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsAbout[language][1]);
			}
			else if (cursor(0, 480, 106, 157))
			{
				sf2d_draw_texture(highlight, 0, 106);
				sftd_draw_textf(robotoS12, 20, 116, RGBA8(0, 0, 0, 255), 12, "%s %s -%d%02d%02d- %s", lang_settingsAbout[language][2], VERSION, YEAR, MONTH + 1, DAY, lang_settingsAbout[language][3]);
			}
			else if (cursor(0, 480, 158, 209))
			{
				sf2d_draw_texture(highlight, 0, 159);
				//sftd_draw_textf(robotoS12, 20, 132, RGBA8(0, 0, 0, 255), 12, "System Version: %s.%s.%s", major, minor, rev);
				sftd_draw_textf(robotoS12, 20, 168, RGBA8(0, 0, 0, 255), 12, "Model: %s %s", modelName, regionName); 
			}

			digitalTime(343, 2);
			batteryStatus(300, 2, 0);
			//androidQuickSettings();
			cursorController();

		sf2d_end_frame();
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(aboutBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		sf2d_swapbuffers();
	}

	sf2d_free_texture(aboutBg);
	sf2d_free_texture(highlight);

	return 0;
}

int developerMenu()
{
	load_PNG(developerBg, "romfs:/developerBg.png");
	load_PNG(highlight, "romfs:/highlight.png");

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(developerBg, 0, 0);
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0); 
		//androidQuickSettings();
		cursorController();
		
		sf2d_end_frame();
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(developerBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		sf2d_swapbuffers();
	}

	sf2d_free_texture(developerBg);
	sf2d_free_texture(highlight);

	return 0;
}

int displayMenu()
{
	load_PNG(displayBg, "romfs:/displayBg.png");
	load_PNG(highlight, "romfs:/highlight.png");
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0);
		//androidQuickSettings();
		cursorController();
		
		sf2d_end_frame();
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		sf2d_swapbuffers();
	}

	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);

	return 0;
}

int securityMenu()
{
	load_PNG(securityBg, "romfs:/securityBg.png");
	load_PNG(highlight, "romfs:/highlight.png");
	
	while (aptMainLoop())
	{
		hidScanInput();
        hidTouchRead(&touch);

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(securityBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 68, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsSecuirty[language][0]); 
		sftd_draw_textf(robotoS12, 20, 116, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsSecuirty[language][1]); 
		sftd_draw_textf(robotoS12, 20, 168, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsSecuirty[language][2]); 
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0);
		//androidQuickSettings();
		
		if (cursor(0, 480, 58, 105))
		{	
			sf2d_draw_texture(highlight, 0, 56);
			sftd_draw_textf(robotoS12, 20, 68, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsSecuirty[language][0]); 
			if (kDown & KEY_A)
			{
				//if (fileExists("system/settings/password.bin", &sdmcArchive))
					//sceIoRemove("system/settings/password.bin");
				/*else*/ if (fileExists("system/settings/pin.bin", &sdmcArchive))
				{
					//sceIoRemove("system/settings/pin.bin");
				//HBKB_CallKeyboard(touch);
				//tempMessage = HBKB_CheckKeyboardInput();
				FILE * password = fopen("system/settings/password.bin", "w");
				fprintf(password, "%s", tempMessage);
				fclose(password);
				//HBKB_Clean();
				}
			}
		}
		
		else if (cursor(0, 480, 106, 157))
		{	
			sf2d_draw_texture(highlight, 0, 105);
			sftd_draw_textf(robotoS12, 20, 116, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsSecuirty[language][1]); 
			if (kDown & KEY_A)
			{
				//if (fileExists("system/settings/password.bin", &sdmcArchive))
					//sceIoRemove("system/settings/password.bin");
				/*else*/ if (fileExists("system/settings/pin.bin", &sdmcArchive))
				{
					//sceIoRemove("system/settings/pin.bin");
				//HBKB_CallKeyboard(touch);
				//tempPin = HBKB_CheckKeyboardInput();
				FILE * pin = fopen("system/settings/pin.bin", "w");
				fprintf(pin, "%s", tempPin);
				fclose(pin);
				//HBKB_Clean();
				}
			}
		}
		
		else if (cursor(0, 480, 158, 209))
		{	
			sf2d_draw_texture(highlight, 0, 157);
			sftd_draw_textf(robotoS12, 20, 168, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsSecuirty[language][2]); 
			if (kDown & KEY_A)
			{
				//if (fileExists("system/settings/password.bin", &sdmcArchive))
					//sceIoRemove("system/settings/password.bin");
				//else if (fileExists("system/settings/pin.bin", &sdmcArchive))
					//sceIoRemove("system/settings/pin.bin");
			}
		}
		
		cursorController();
		
		sf2d_end_frame();
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(securityBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		sf2d_swapbuffers();
	}

	sf2d_free_texture(securityBg);
	sf2d_free_texture(highlight);

	return 0;
}

int settingsHighlight()
{
	u32 kDown = hidKeysDown();

	if (cursor(0, 198, 75, 133))
	{
		sf2d_draw_texture(wifi_highlight, 0, 87);
		sftd_draw_textf(robotoS12, 48, 106, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][0]);
		/*if (kDown & KEY_A)
		{
			settingsUnload();
		}*/
	}
	else if (cursor(0, 198, 134, 174))
	{
		sf2d_draw_texture(display_highlight, 0, 135);
		sftd_draw_textf(robotoS12, 48, 153, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][2]);
		/*if (kDown & KEY_A)
		{
			settingsUnload();
		}*/
	}
	else if (cursor(0, 198, 175, 240))
	{
		sf2d_draw_texture(developeroptions_highlight, 0, 183);
		sftd_draw_textf(robotoS12, 48, 202, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][4]);
		/*if (kDown & KEY_A)
		{
			settingsUnload();
		}*/
	}
	else if (cursor(203, 400, 75, 133))
	{
		sf2d_draw_texture(security_highlight, 199, 87);
		sftd_draw_textf(robotoS12, 250, 106, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][1]);
		if (kDown & KEY_A)
		{
			settingsUnload();
			securityMenu();
		}
	}
	else if (cursor(203, 400, 134, 174))
	{
		sf2d_draw_texture(performance_highlight, 203, 135);
		sftd_draw_textf(robotoS12, 250, 153, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][3]);
		/*if (kDown & KEY_A)
		{
			settingsUnload();
		}*/
	}
	else if (cursor(203, 400, 175, 240))
	{
		sf2d_draw_texture(about_highlight, 203, 183);
		sftd_draw_textf(robotoS12, 250, 202, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][5]);
		if (kDown & KEY_A)
		{
			settingsUnload();
			aboutMenu();
		}
	}
	
	return 0;
}

int settingsUnload()
{
	sf2d_free_texture(settingsBg);
	sf2d_free_texture(about_highlight);
	sf2d_free_texture(display_highlight);
	sf2d_free_texture(developeroptions_highlight);
	sf2d_free_texture(performance_highlight);
	sf2d_free_texture(security_highlight);
	sf2d_free_texture(wifi_highlight);
	return 0;
}

int settingsMenu()
{
	load_PNG(settingsBg, "romfs:/settingsBg.png");
	load_PNG(about_highlight, "romfs:/about_highlight.png");
	load_PNG(display_highlight, "romfs:/display_highlight.png");
	load_PNG(developeroptions_highlight, "romfs:/developersoptions_highlight.png");
	load_PNG(performance_highlight, "romfs:/performance_highlight.png");
	load_PNG(security_highlight, "romfs:/security_highlight.png");
	load_PNG(wifi_highlight, "romfs:/wifi_highlight.png");

	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(settingsBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 48, 106, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][0]);
		sftd_draw_textf(robotoS12, 48, 153, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][2]);
		sftd_draw_textf(robotoS12, 48, 202, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][4]);
		sftd_draw_textf(robotoS12, 250, 106, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][1]);
		sftd_draw_textf(robotoS12, 250, 153, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][3]);
		sftd_draw_textf(robotoS12, 250, 202, RGBA8(0, 0, 0, 255), 12, "%s", lang_settingsMain[language][5]);
		
		settingsHighlight();
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0); 
		//androidQuickSettings();
		cursorController();
		
		sf2d_end_frame();
		
		navbarControls(0); 
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			settingsUnload();
			appDrawer();
		}
		
		sf2d_swapbuffers();
	}
	
	settingsUnload();
	
	return 0;
}

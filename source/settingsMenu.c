#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "language.h"
#include "lockScreen.h"
#include "main.h"
#include "powerMenu.h"
#include "screenshot.h"
#include "settingsMenu.h"
#include "utils.h"

struct settingsFontColor SettingfontColor;
struct timeAndBatteryStatusFontColor fontColorTime;

void flashUpdate()
{
	load_PNG(recoverybg, "/3ds/Cyanogen3DS/android_bootable_recovery/res/images/recoverybg.png.png");
	
	while (aptMainLoop())
	{			
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(recoverybg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "Flashing zip...");
		
		if (fileExists("/3ds/Cyanogen3DS/UPDATE.zip"))
		{
			extractZip("/3ds/Cyanogen3DS/UPDATE.zip", "/3ds/");
			sftd_draw_textf(robotoS12, 20, 88, fontColor, 12, "Installed Successfully.");
			sftd_draw_textf(robotoS12, 20, 108, fontColor, 12, "Exiting..");
			sf2d_free_texture(recoverybg);
			longjmp(exitJmp, 1);
		}
		
		sf2d_end_frame();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(recoverybg);
}

int aboutMenu()
{
	if (DARK == 1)
	{
		load_PNG(aboutBg, "/3ds/Cyanogen3DS/system/settings/Dark/aboutBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(aboutBg, aboutBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, aboutBg);
	setBilinearFilter(1, highlight);
	
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
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);

		sf2d_draw_texture(aboutBg, 0, 0);

		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsAbout[language][0]);
		sftd_draw_textf(robotoS12, 20, 83, fontColor, 12, "%s", lang_settingsAbout[language][1]);
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s %s -%d%02d%02d- %s", lang_settingsAbout[language][2], VERSION, YEAR, MONTH + 1, DAY, lang_settingsAbout[language][3]);
		//sftd_draw_textf(robotoS12, 20, 132, fontColor, 12, "System Version: %s.%s.%s", major, minor, rev);
		sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "Model: %s %s", modelName, regionName);
		sftd_draw_textf(robotoS12, 20, 184, fontColor, 12, "MAC Address: %s", getMacAddress());

		if (cursor(0, 480, 58, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsAbout[language][0]);
			sftd_draw_textf(robotoS12, 20, 83, fontColor, 12, "%s", lang_settingsAbout[language][1]);
			/*if (experimentalF == 1)
			{	
				if (kDown & KEY_A)
				{
					sf2d_free_texture(aboutBg);
					sf2d_free_texture(highlight);
					updatesMenu();
				}
			}*/
		}
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(aboutBg);
			sf2d_free_texture(highlight);
		}
		else if (cursor(0, 480, 106, 157))
		{
			sf2d_draw_texture(highlight, 0, 107);
			sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s %s -%d%02d%02d- %s", lang_settingsAbout[language][2], VERSION, YEAR, MONTH + 1, DAY, lang_settingsAbout[language][3]);
			//sftd_draw_textf(robotoS12, 20, 132, fontColor, 12, "System Version: %s.%s.%s", major, minor, rev);
		}
		else if (cursor(0, 480, 158, 209))
		{
			sf2d_draw_texture(highlight, 0, 158);
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "Model: %s %s", modelName, regionName); 
			sftd_draw_textf(robotoS12, 20, 184, fontColor, 12, "MAC Address: %s", getMacAddress());
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
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(aboutBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(aboutBg);
	sf2d_free_texture(highlight);

	return 0;
}

int developerMenu()
{
	if (DARK == 1)
	{
		load_PNG(developerBg, "/3ds/Cyanogen3DS/system/settings/Dark/developerBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		load_PNG(onSwitch, "/3ds/Cyanogen3DS/system/settings/onSwitch.png");
		load_PNG(offSwitch, "/3ds/Cyanogen3DS/system/settings/offSwitch.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(developerBg, developerBgPath);
		load_PNG(highlight, highlightPath);
		load_PNG(onSwitch, onSwitchPath);
		load_PNG(offSwitch, offSwitchPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, developerBg);
	setBilinearFilter(1, highlight);
	setBilinearFilter(1, onSwitch);
	setBilinearFilter(1, offSwitch);
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(developerBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 76, fontColor, 12, "Switch display");
		sftd_draw_textf(robotoS12, 20, 122, fontColor, 12, "%s", lang_settingsDeveloperOptions[language][2]);
		sftd_draw_textf(robotoS12, 20, 173, fontColor, 12, "%s", lang_settingsDeveloperOptions[language][3]);
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 54);
			sftd_draw_textf(robotoS12, 20, 76, fontColor, 12, "Switch display");
			if (experimentalF == 1)
			{
				if (screenDisplay == 0)
				{
					sf2d_draw_texture(offSwitch, 355, 70);
				
					if (kDown & KEY_A)
					{
						screenDisplay = 1;
						FILE * switchDisplay = fopen("/3ds/Cyanogen3DS/system/settings/switchDisplay.bin", "w");
						fprintf(switchDisplay, "%d", screenDisplay);
						fclose(switchDisplay);
					}
				}
				else if (screenDisplay == 1)
				{
					sf2d_draw_texture(onSwitch, 355, 70);
			
					if (kDown & KEY_A)
					{
						screenDisplay = 0;
						FILE * switchDisplay = fopen("/3ds/Cyanogen3DS/system/settings/switchDisplay.bin", "w");
						fprintf(switchDisplay, "%d", screenDisplay);
						fclose(switchDisplay);
					}
				}
			}
		}
		else if (cursor(0, 480, 105, 155))
		{
			sf2d_draw_texture(highlight, 0, 104);
			sftd_draw_textf(robotoS12, 20, 122, fontColor, 12, "%s", lang_settingsDeveloperOptions[language][2]);
			if (experimentalF == 0)
			{
				sf2d_draw_texture(offSwitch, 355, 119);
				
				if (kDown & KEY_A)
				{
					experimentalF = 1;
					FILE * experimentalFeatures = fopen("/3ds/Cyanogen3DS/system/settings/experimentalFeatures.bin", "w");
					fprintf(experimentalFeatures, "%d", experimentalF);
					fclose(experimentalFeatures);
				}
			}
			else if (experimentalF == 1)
			{
				sf2d_draw_texture(onSwitch, 355, 119);
			
				if (kDown & KEY_A)
				{
					experimentalF = 0;
					FILE * experimentalFeatures = fopen("/3ds/Cyanogen3DS/system/settings/experimentalFeatures.bin", "w");
					fprintf(experimentalFeatures, "%d", experimentalF);
					fclose(experimentalFeatures);
				}
			}
		}
		else if (cursor(0, 480, 156, 205))
		{
			sf2d_draw_texture(highlight, 0, 153);
			sftd_draw_textf(robotoS12, 20, 173, fontColor, 12, "%s", lang_settingsDeveloperOptions[language][3]);
			
			if (DARK == 0)
			{
				sf2d_draw_texture(offSwitch, 355, 166);
				
				if (kDown & KEY_A)
				{
					DARK = 1;
					FILE * darkTheme = fopen("/3ds/Cyanogen3DS/system/settings/darkTheme.bin", "w");
					fprintf(darkTheme, "%d", DARK);
					fclose(darkTheme);
					sf2d_free_texture(developerBg);
					sf2d_free_texture(highlight);
					load_PNG(developerBg, "/3ds/Cyanogen3DS/system/settings/Dark/developerBg.png");
					load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
					fontColor = LITEGRAY;
				}
			}
			else if (DARK == 1)
			{
				sf2d_draw_texture(onSwitch, 355, 166);
			
				if (kDown & KEY_A)
				{
					DARK = 0;
					FILE * darkTheme = fopen("/3ds/Cyanogen3DS/system/settings/darkTheme.bin", "w");
					fprintf(darkTheme, "%d", DARK);
					fclose(darkTheme);
					sf2d_free_texture(developerBg);
					sf2d_free_texture(highlight);
					load_PNG(developerBg, developerBgPath);
					load_PNG(highlight, highlightPath);
					fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
				}
			}
		}
		
		if (experimentalF == 0)
			sf2d_draw_texture(offSwitch, 355, 119);
		else
			sf2d_draw_texture(onSwitch, 355, 119);
		
		if (DARK == 0)
			sf2d_draw_texture(offSwitch, 355, 166);
		else
			sf2d_draw_texture(onSwitch, 355, 166);
		
		if (screenDisplay == 0)
			sf2d_draw_texture(offSwitch, 355, 70);
		else
			sf2d_draw_texture(onSwitch, 355, 70);
		
		if (screenDisplay == 0)
		{
			digitalTime(352, 2, 0);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
		}
		
		cursorController();
		
		sf2d_end_frame();
		
		switchDisplayModeOn(2);
		
		navbarControls(0);
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(developerBg);
			sf2d_free_texture(highlight);
			sf2d_free_texture(offSwitch);
			sf2d_free_texture(onSwitch);
			settingsMenu();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(developerBg);
			sf2d_free_texture(highlight);
			sf2d_free_texture(offSwitch);
			sf2d_free_texture(onSwitch);
			settingsMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(developerBg);
	sf2d_free_texture(highlight);
	sf2d_free_texture(offSwitch);
	sf2d_free_texture(onSwitch);

	return 0;
}

int displayMenu()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "/3ds/Cyanogen3DS/system/settings/Dark/displayBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, displayBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsDisplay[language][0]);
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsDisplay[language][1]);
		sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsDisplay[language][2]);
		sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsDisplay[language][3]);
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsDisplay[language][0]);
			if (experimentalF == 1)
			{
				if (kDown & KEY_A)
				{
					sf2d_free_texture(displayBg);
					sf2d_free_texture(highlight);
					displayThemes();
				}
			}
		}
		else if (cursor(0, 480, 105, 155))
		{
			sf2d_draw_texture(highlight, 0, 105);
			sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsDisplay[language][1]);
			if (kDown & KEY_A)
			{	
				sf2d_free_texture(displayBg);
				sf2d_free_texture(highlight);
				displayTime();
			}
		}
		else if (cursor(0, 480, 156, 205))
		{
			sf2d_draw_texture(highlight, 0, 154);
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsDisplay[language][2]);
		}
		else if (cursor(0, 480, 206, 240))
		{
			sf2d_draw_texture(highlight, 0, 202);
			sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsDisplay[language][3]);
			if (kDown & KEY_A)
			{	
				sf2d_free_texture(displayBg);
				sf2d_free_texture(highlight);
				displayMiscellaneous();
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
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);

	return 0;
}

int displayThemes()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "/3ds/Cyanogen3DS/system/settings/Dark/displayBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, displayBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsThemes[language][0]);
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsThemes[language][1]);
		sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsThemes[language][2]);
		sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsThemes[language][3]);
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsThemes[language][0]);
			if (kDown & KEY_A)
				displayThemesManager();
		}
		else if (cursor(0, 480, 105, 155))
		{
			sf2d_draw_texture(highlight, 0, 105);
			sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsThemes[language][1]);
		}
		else if (cursor(0, 480, 156, 205))
		{
			sf2d_draw_texture(highlight, 0, 154);
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsThemes[language][2]);
		}
		else if (cursor(0, 480, 206, 240))
		{
			sf2d_draw_texture(highlight, 0, 202);
			sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsThemes[language][3]);
			if (kDown & KEY_A)
				displayIconPack();
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
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			displayMenu();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			displayMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);

	return 0;
}

int displayThemesManager()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "/3ds/Cyanogen3DS/system/settings/Dark/displayBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, displayBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 64, fontColor, 12, "SAO");
		sftd_draw_textf(robotoS12, 20, 81, fontColor, 12, "Press (x) to switch back to default");
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 64, fontColor, 12, "SAO");
			sftd_draw_textf(robotoS12, 20, 81, fontColor, 12, "Press (x) to switch back to default");
				
			// Just for testing purposes - confirmed working.
			if (kDown & KEY_A)
			{
				strcpy(themeDirPath, "/3ds/Cyanogen3DS/system/themes/SAO");
				FILE * themeTxt = fopen("/3ds/Cyanogen3DS/system/settings/theme.bin", "w");
				fprintf(themeTxt, "%s", themeDirPath);
				fclose(themeTxt);
				themesLoad();
				themesReload();
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
		
		// Just for testing purposes - confirmed working.
		if (kDown & KEY_X)
		{
			strcpy(themeDirPath, "/3ds/Cyanogen3DS/system");
			FILE * themeTxt = fopen("/3ds/Cyanogen3DS/system/settings/theme.bin", "w");
			fprintf(themeTxt, "%s", themeDirPath);
			fclose(themeTxt);
			themesLoad();
			themesReload();
		}
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			displayThemes();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			displayThemes();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);

	return 0;
}

int displayIconPack()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "/3ds/Cyanogen3DS/system/settings/Dark/displayBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, displayBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 64, fontColor, 12, "SAO");
		sftd_draw_textf(robotoS12, 20, 81, fontColor, 12, "Press (x) to switch back to default");
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 64, fontColor, 12, "SAO");
			sftd_draw_textf(robotoS12, 20, 81, fontColor, 12, "Press (x) to switch back to default");
				
			// Just for testing purposes - confirmed working.
			if (kDown & KEY_A)
			{
				strcpy(appDirPath, "/3ds/Cyanogen3DS/system/icons/SAO");
				FILE * iconPackTxt = fopen("/3ds/Cyanogen3DS/system/settings/iconpack.bin", "w");
				fprintf(iconPackTxt, "%s", appDirPath);
				fclose(iconPackTxt);
				iconPackLoad();
				iconPackReload();
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
		
		//Just for testing purposes - confirmed working.
		if (kDown & KEY_X)
		{
			strcpy(appDirPath, "/3ds/Cyanogen3DS/system/icons/Default");
			FILE * iconPackTxt = fopen("/3ds/Cyanogen3DS/system/settings/iconpack.bin", "w");
			fprintf(iconPackTxt, "%s", appDirPath);
			fclose(iconPackTxt);
			iconPackLoad();
			iconPackReload();
		} 
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			displayThemes();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			displayThemes();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);

	return 0;
}

void replaceAsset(char tempData[], char path[], char imgPath[], char redirectPath[])
{
	strcpy(tempData, path);
	strcat(tempData, imgPath); 
	strcpy(redirectPath, tempData);
}

void themesLoad()
{	
	strcpy(themeDirPath, setFileDefaultsChar("/3ds/Cyanogen3DS/system/settings/theme.bin", "/3ds/Cyanogen3DS/system", themeDirPath));

	char highlightImg[100] = "/settings/highlight.png";
	char settingsBgImg[100] = "/settings/settingsBg.png";
	char displayBgImg[100] = "/settings/displayBg.png";
	char aboutBgImg[100] = "/settings/aboutBg.png";
	char developerBgImg[100] = "/settings/developerBg.png";
	char performanceBgImg[100] = "/settings/performanceBg.png";
	char performance2BgImg[100] = "/settings/performanceBg2.png";
	char securityBgImg[100] = "/settings/securityBg.png";
	char updatesBgImg[100] = "/settings/updatesBg.png";
	char offSwitchImg[100] = "/settings/offswitch.png";
	char onSwitchImg[100] = "/settings/onswitch.png";
	char selectImg[100] = "/settings/select.png";
	
	char aboutImg[100] = "/settings/about.png";
	char developerImg[100] = "/settings/developeroptions.png";
	char performanceImg[100] = "/settings/performance.png";
	char securityImg[100] = "/settings/security.png";
	char themesImg[100] = "/settings/themes.png";
	char wifiImg[100] = "/settings/wifi.png";
	
	char fmBgImg[100] = "/app/filemanager/filemanagerBg.png";
	char fmSelectorImg[100] = "/app/filemanager/bar.png";
	char diriconImg[100] = "/app/filemanager/dir.png";
	
	char quickSettingsBgImg[100] = "/home/menu/quickSettings.png";
	char backdropImg[100] = "/home/icons/backdrop.png";
	char navbarImg[100] = "/home/icons/navbar.png";
	char navbarHighlightImg[100] = "/home/icons/navbarHighlight.png";
	
	char cursorImg[100] = "/cursor/cursor.png";
	
	char backgroundData[100] = "/settings/background.bin";
	
	char rgbValues[100] = "/settings/rgb.bin";
	char appDrawerFontColor[100] = "/app/rgb.bin";
	char fileManagerFontColor[100] = "/app/filemanager/rgb.bin";
	//char galleryFontColor[100] = "/app/gallery/rgb.bin";
	//char gameFontColor[100] = "/app/game/rgb.bin";
	//char apolloFontColor[100] = "/app/apollo/rgb.bin";
	char settingsFontColor[100] = "/settings/srgb.bin";
	char timeAndBatteryFontColor[100] = "/home/rgb.bin";
	char lockScreenWidgetFontColor[100] = "/app/clock/rgb.bin";
	
	replaceAsset(tempData, themeDirPath, highlightImg, highlightPath);
	replaceAsset(tempData, themeDirPath, aboutBgImg, aboutBgPath);
	replaceAsset(tempData, themeDirPath, developerBgImg, developerBgPath);
	replaceAsset(tempData, themeDirPath, performanceBgImg, performanceBgPath);
	replaceAsset(tempData, themeDirPath, performance2BgImg, performance2BgPath);
	replaceAsset(tempData, themeDirPath, securityBgImg, securityBgPath);
	replaceAsset(tempData, themeDirPath, updatesBgImg, updatesBgPath);
	replaceAsset(tempData, themeDirPath, offSwitchImg, offSwitchPath);
	replaceAsset(tempData, themeDirPath, onSwitchImg, onSwitchPath);
	replaceAsset(tempData, themeDirPath, selectImg, selectPath);
	replaceAsset(tempData, themeDirPath, aboutImg, aboutPath);
	replaceAsset(tempData, themeDirPath, developerImg, developerPath);
	replaceAsset(tempData, themeDirPath, performanceImg, performancePath);
	replaceAsset(tempData, themeDirPath, securityImg, securityPath);
	replaceAsset(tempData, themeDirPath, themesImg, themesPath);
	replaceAsset(tempData, themeDirPath, wifiImg, wifiPath);
	replaceAsset(tempData, themeDirPath, settingsBgImg, settingsBgPath);
	replaceAsset(tempData, themeDirPath, displayBgImg, displayBgPath);
	replaceAsset(tempData, themeDirPath, fmBgImg, fmBgPath);
	replaceAsset(tempData, themeDirPath, fmSelectorImg, fmSelectorPath);
	replaceAsset(tempData, themeDirPath, diriconImg, diriconPath);
	replaceAsset(tempData, themeDirPath, quickSettingsBgImg, quickSettingsBgPath);
	replaceAsset(tempData, themeDirPath, navbarImg, navbarPath);
	replaceAsset(tempData, themeDirPath, navbarHighlightImg, navbarHighlightPath);
	replaceAsset(tempData, themeDirPath, backdropImg, backdropPath);
	replaceAsset(tempData, themeDirPath, cursorImg, cursorPath);
	replaceAsset(tempData, themeDirPath, backgroundData, backgroundPath);
	replaceAsset(tempData, themeDirPath, rgbValues, rgbValuesPath);
	replaceAsset(tempData, themeDirPath, appDrawerFontColor, appDrawerFontColorPath);
	replaceAsset(tempData, themeDirPath, fileManagerFontColor, fileManagerFontColorPath);
	//replaceAsset(tempData, themeDirPath, galleryFontColor, galleryFontColorPath);
	//replaceAsset(tempData, themeDirPath, gameFontColor, gameFontColorPath);
	//replaceAsset(tempData, themeDirPath, apolloFontColor, apolloFontColorPath);
	replaceAsset(tempData, themeDirPath, settingsFontColor, settingsFontColorPath);
	replaceAsset(tempData, themeDirPath, timeAndBatteryFontColor, timeAndBatteryFontColorPath);
	replaceAsset(tempData, themeDirPath, lockScreenWidgetFontColor, clockWidgetFontColorPath);
	
	FILE *temp;
	 
	if (!(fileExists(rgbValuesPath)))
	{
		temp = fopen(rgbValuesPath, "w");
		fprintf(temp, "0\n149\n135");
		fclose(temp);
	}
	
	temp = fopen(rgbValuesPath, "r");
	fscanf(temp, "%d %d %d", &r, &g, &b);
	fclose(temp);
	
	strcpy(backgroundPath, setFileDefaultsChar(backgroundPath, "/3ds/Cyanogen3DS/system/framework/framework-res/res/background1.png", backgroundPath));
}

void themesReload()
{
	sf2d_free_texture(background);
	sf2d_free_texture(navbar);
	sf2d_free_texture(navbarHighlight);
	sf2d_free_texture(quickSettings);
	sf2d_free_texture(cursor);
	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);
	
	load_PNG(background, backgroundPath);
	load_PNG(navbar, navbarPath);
	load_PNG(navbarHighlight, navbarHighlightPath);
	load_PNG(quickSettings, quickSettingsBgPath);
	load_PNG(cursor, cursorPath);
	load_PNG(displayBg, displayBgPath);
	load_PNG(highlight, highlightPath);
	
	FILE *temp;
	 
	if (!(fileExists(settingsFontColorPath)))
	{
		temp = fopen(settingsFontColorPath, "w");
		fprintf(temp, "0\n0\n0");
		fclose(temp);
	}
	
	temp = fopen(settingsFontColorPath, "r");
	fscanf(temp, "%d %d %d", &SettingfontColor.r, &SettingfontColor.g, &SettingfontColor.b);
	fclose(temp);
	
	FILE *temp2;
	 
	if (!(fileExists(timeAndBatteryFontColorPath)))
	{
		temp2 = fopen(timeAndBatteryFontColorPath, "w");
		fprintf(temp2, "255\n255\n255");
		fclose(temp2);
	}
	
	temp2 = fopen(timeAndBatteryFontColorPath, "r");
	fscanf(temp2, "%d %d %d", &fontColorTime.r, &fontColorTime.g, &fontColorTime.b);
	fclose(temp2);
	
	setBilinearFilter(1, background);
	setBilinearFilter(1, cursor);
	setBilinearFilter(1, quickSettings);
	setBilinearFilter(1, navbar);
	setBilinearFilter(1, navbarHighlight);
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);
}

void iconPackLoad()
{
	strcpy(appDirPath, setFileDefaultsChar("/3ds/Cyanogen3DS/system/settings/iconpack.bin", "/3ds/Cyanogen3DS/system/icons/Default", appDirPath));
	
	char allappsImg[50] = "/allapps/ic_allapps.png";
	char allapps_pressedImg[50] = "/allapps/ic_allapps_pressed.png";
	char apolloImg[50] = "/music/ic_launcher_apollo.png";
	char browserImg[50] = "/browser/ic_launcher_browser.png";
	char clockImg[50] = "/clock/ic_launcher_clock.png";
	char fmImg[50] = "/filemanager/ic_launcher_filemanager.png";
	char galleryImg[50] = "/gallery/ic_launcher_gallery.png";
	char gameImg[50] = "/game/ic_launcher_game.png";
	char messagesImg[50] = "/messenger/ic_launcher_messenger.png";
	char settingsImg[50] = "/settings/ic_launcher_settings.png";
	
	replaceAsset(tempData, appDirPath, allappsImg, allappsPath);
	replaceAsset(tempData, appDirPath, allapps_pressedImg, allapps_pressedPath);
	replaceAsset(tempData, appDirPath, apolloImg, apolloPath);
	replaceAsset(tempData, appDirPath, browserImg, browserPath);
	replaceAsset(tempData, appDirPath, clockImg, clockPath);
	replaceAsset(tempData, appDirPath, fmImg, fmPath);
	replaceAsset(tempData, appDirPath, galleryImg, galleryPath);
	replaceAsset(tempData, appDirPath, gameImg, gamePath);
	replaceAsset(tempData, appDirPath, messagesImg, messagesPath);
	replaceAsset(tempData, appDirPath, settingsImg, settingsPath);
}

void iconPackReload()
{
	sf2d_free_texture(ic_allapps);
	sf2d_free_texture(ic_allapps_pressed);
	sf2d_free_texture(ic_launcher_apollo);
	sf2d_free_texture(ic_launcher_browser);
	sf2d_free_texture(ic_launcher_messenger);
	sf2d_free_texture(ic_launcher_settings);
		
	load_PNG(ic_allapps, allappsPath);
	load_PNG(ic_allapps_pressed, allapps_pressedPath);
	load_PNG(ic_launcher_apollo, apolloPath);
	load_PNG(ic_launcher_browser, browserPath);
	load_PNG(ic_launcher_messenger, messagesPath);
	load_PNG(ic_launcher_settings, settingsPath);
	
	setBilinearFilter(1, ic_launcher_browser);
	setBilinearFilter(1, ic_launcher_messenger);
	setBilinearFilter(1, ic_launcher_apollo);
	setBilinearFilter(1, ic_launcher_settings);
	
	displayIconPack();
}

int displayTime()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "/3ds/Cyanogen3DS/system/settings/Dark/displayBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		load_PNG(onSwitch, "/3ds/Cyanogen3DS/system/settings/onSwitch.png");
		load_PNG(offSwitch, "/3ds/Cyanogen3DS/system/settings/offSwitch.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, displayBgPath);
		load_PNG(highlight, highlightPath);
		load_PNG(onSwitch, onSwitchPath);
		load_PNG(offSwitch, offSwitchPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);
	setBilinearFilter(1, onSwitch);
	setBilinearFilter(1, offSwitch);
	
	FILE * timeSetTxt;
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		if (hrTime == 0)
			sf2d_draw_texture(offSwitch, 355, 70);
		else if (hrTime == 1)
			sf2d_draw_texture(onSwitch, 355, 70);
		
		sftd_draw_textf(robotoS12, 20, 73, fontColor, 12, "%s", lang_settingsTime[language][0]);
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 73, fontColor, 12, "%s", lang_settingsTime[language][0]);
			if (hrTime == 0)
			{
				sf2d_draw_texture(offSwitch, 355, 70);
				
				if (kDown & KEY_A)
				{
					hrTime = 1;
					timeSetTxt = fopen("/3ds/Cyanogen3DS/system/app/clock/timeSet.bin", "w");
					fprintf(timeSetTxt, "%d", hrTime);
					fclose(timeSetTxt);
				}
			}
			else if (hrTime == 1)
			{
				sf2d_draw_texture(onSwitch, 355, 70);
			
				if (kDown & KEY_A)
				{
					hrTime = 0;
					timeSetTxt = fopen("/3ds/Cyanogen3DS/system/app/clock/timeSet.bin", "w");
					fprintf(timeSetTxt, "%d", hrTime);
					fclose(timeSetTxt);
				}
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
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			sf2d_free_texture(offSwitch);
			sf2d_free_texture(onSwitch);
			displayMenu();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			sf2d_free_texture(offSwitch);
			sf2d_free_texture(onSwitch);
			displayMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);
	sf2d_free_texture(offSwitch);
	sf2d_free_texture(onSwitch);

	return 0;
}

int displayMiscellaneous()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "/3ds/Cyanogen3DS/system/settings/Dark/displayBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		load_PNG(onSwitch, "/3ds/Cyanogen3DS/system/settings/onSwitch.png");
		load_PNG(offSwitch, "/3ds/Cyanogen3DS/system/settings/offSwitch.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, displayBgPath);
		load_PNG(highlight, highlightPath);
		load_PNG(onSwitch, onSwitchPath);
		load_PNG(offSwitch, offSwitchPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);
	setBilinearFilter(1, onSwitch);
	setBilinearFilter(1, offSwitch);
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		if (widgetActivator == 0)
			sf2d_draw_texture(offSwitch, 355, 65);
		else if (widgetActivator == 1)
			sf2d_draw_texture(onSwitch, 355, 65);
		if (bootAnimActivator == 0)
			sf2d_draw_texture(offSwitch, 355, 164);
		else if (bootAnimActivator == 1)
			sf2d_draw_texture(onSwitch, 355, 164);
		
		sf2d_draw_texture(offSwitch, 355, 115);
		sf2d_draw_texture(offSwitch, 355, 208);
		
		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsMiscellaneous[language][0]);
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsMiscellaneous[language][1]);
		sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsMiscellaneous[language][2]);
		sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsMiscellaneous[language][3]);
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsMiscellaneous[language][0]);
			if (widgetActivator == 0)
			{
				sf2d_draw_texture(offSwitch, 355, 65);
				
				if (kDown & KEY_A)
				{
					widgetActivator = 1;
					FILE * widgetActivation = fopen("/3ds/Cyanogen3DS/system/widget/widgetActivator.bin", "w");
					fprintf(widgetActivation, "%d", widgetActivator);
					fclose(widgetActivation);
				}
			}
			else if (widgetActivator == 1)
			{
				sf2d_draw_texture(onSwitch, 355, 65);
			
				if (kDown & KEY_A)
				{
					widgetActivator = 0;
					FILE * widgetActivation = fopen("/3ds/Cyanogen3DS/system/widget/widgetActivator.bin", "w");
					fprintf(widgetActivation, "%d", widgetActivator);
					fclose(widgetActivation);
				}
			}
		}
		else if (cursor(0, 480, 105, 155))
		{
			sf2d_draw_texture(highlight, 0, 105);
			sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsMiscellaneous[language][1]);
			sf2d_draw_texture(offSwitch, 355, 115);
		}
		else if (cursor(0, 480, 156, 205))
		{
			sf2d_draw_texture(highlight, 0, 154);
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsMiscellaneous[language][2]);
			if (bootAnimActivator == 0)
			{
				sf2d_draw_texture(offSwitch, 355, 164);
				
				if (kDown & KEY_A)
				{
					bootAnimActivator = 1;
					FILE * bootAnimActivation = fopen("/3ds/Cyanogen3DS/system/boot/bootAnimActivator.bin", "w");
					fprintf(bootAnimActivation, "%d", bootAnimActivator);
					fclose(bootAnimActivation);
				}
			}
			else if (bootAnimActivator == 1)
			{
				sf2d_draw_texture(onSwitch, 355, 164);
			
				if (kDown & KEY_A)
				{
					bootAnimActivator = 0;
					FILE * bootAnimActivation = fopen("/3ds/Cyanogen3DS/system/boot/bootAnimActivator.bin", "w");
					fprintf(bootAnimActivation, "%d", bootAnimActivator);
					fclose(bootAnimActivation);
				}
			}
		}
		else if (cursor(0, 480, 206, 240))
		{
			sf2d_draw_texture(highlight, 0, 202);
			sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsMiscellaneous[language][3]);
			sf2d_draw_texture(offSwitch, 355, 208);
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
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			sf2d_free_texture(offSwitch);
			sf2d_free_texture(onSwitch);
			displayMenu();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(displayBg);
			sf2d_free_texture(highlight);
			sf2d_free_texture(offSwitch);
			sf2d_free_texture(onSwitch);
			displayMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(displayBg);
	sf2d_free_texture(highlight);
	sf2d_free_texture(offSwitch);
	sf2d_free_texture(onSwitch);

	return 0;
}

int performanceMenu()
{
	if (DARK == 1)
	{
		load_PNG(performanceBg, "/3ds/Cyanogen3DS/system/settings/Dark/performanceBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(performanceBg, performanceBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, performanceBg);
	setBilinearFilter(1, highlight);
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(performanceBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsPerformance[language][0]);
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsPerformance[language][1]);
		sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsPerformance[language][2]);
		sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsPerformance[language][3]);
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsPerformance[language][0]);
		}
		else if (cursor(0, 480, 105, 155))
		{
			sf2d_draw_texture(highlight, 0, 105);
			sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsPerformance[language][1]);
		}
		else if (cursor(0, 480, 156, 205))
		{
			sf2d_draw_texture(highlight, 0, 154);
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsPerformance[language][2]);
			if (kDown & KEY_A)
				storageMenu();
		}
		else if (cursor(0, 480, 206, 240))
		{
			sf2d_draw_texture(highlight, 0, 202);
			sftd_draw_textf(robotoS12, 20, 213, fontColor, 12, "%s", lang_settingsPerformance[language][3]);
			if (kDown & KEY_A)
				batteryMenu();
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
		
		if (kDown & KEY_Y)
			powerMenu(); 
		
		if (kDown & KEY_L)
			lockScreen();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(performanceBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(performanceBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(performanceBg);
	sf2d_free_texture(highlight);

	return 0;
}

int storageMenu()
{
	if (DARK == 1)
	{
		load_PNG(performanceBg2, "/3ds/Cyanogen3DS/system/settings/Dark/performanceBg2.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(performanceBg2, performance2BgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, performanceBg2);
	setBilinearFilter(1, highlight);
	
	FS_ArchiveResource resource = {0};
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(performanceBg2, 0, 0);
		
		FSUSER_GetArchiveResource(&resource, SYSTEM_MEDIATYPE_SD);
		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "SD: %.1f MB", ((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0);
		sf2d_draw_rectangle(20, 86, 360, 10, RGBA8(206, 215, 219, 255));
		sf2d_draw_rectangle(20, 86, ((((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) / (((u64) resource.totalClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) * 360) - 20, 10, RGBA8(r, g, b, 255));
		
		FSUSER_GetArchiveResource(&resource, SYSTEM_MEDIATYPE_CTR_NAND);
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "CTR NAND: %.1f MB", ((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0);
		sf2d_draw_rectangle(20, 134, 360, 10, RGBA8(206, 215, 219, 255));
		sf2d_draw_rectangle(20, 134, ((((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) / (((u64) resource.totalClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) * 360) - 20, 10, RGBA8(r, g, b, 255));
		
		if (screenDisplay == 0)
		{
			digitalTime(352, 2, 0);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
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
			sf2d_free_texture(performanceBg2);
			sf2d_free_texture(highlight);
			performanceMenu();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(performanceBg2);
			sf2d_free_texture(highlight);
			performanceMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(performanceBg2);
	sf2d_free_texture(highlight);

	return 0;
}

int batteryMenu()
{
	if (DARK == 1)
	{
		load_PNG(performanceBg, "/3ds/Cyanogen3DS/system/settings/Dark/performanceBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(performanceBg, performanceBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	load_PNG(deselect, "/3ds/Cyanogen3DS/system/settings/deselect.png");
	load_PNG(select, selectPath);
	
	setBilinearFilter(1, performanceBg);
	setBilinearFilter(1, highlight);
	setBilinearFilter(1, deselect);
	setBilinearFilter(1, select);
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(performanceBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 70, fontColor, 12, "%s", lang_settingsBattery[language][0]);
		sftd_draw_textf(robotoS12, 20, 120, fontColor, 12, "%s", lang_settingsBattery[language][1]);
		sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsBattery[language][2]);
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 70, fontColor, 12, "%s", lang_settingsBattery[language][0]);
		}
		else if (cursor(0, 480, 105, 155))
		{
			sf2d_draw_texture(highlight, 0, 105);
			sftd_draw_textf(robotoS12, 20, 120, fontColor, 12, "%s", lang_settingsBattery[language][1]);
		}
		else if (cursor(0, 480, 156, 205))
		{
			sf2d_draw_texture(highlight, 0, 154);
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsBattery[language][2]);
			if (kDown & KEY_A)
				storageMenu();
		}
		
		sf2d_draw_texture(deselect, 370, 70);
		sf2d_draw_texture(deselect, 370, 120);
		sf2d_draw_texture(deselect, 370, 168);
		
		if (screenDisplay == 0)
		{
			digitalTime(352, 2, 0);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
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
			sf2d_free_texture(performanceBg);
			sf2d_free_texture(highlight);
			performanceMenu();
		}
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(performanceBg);
			sf2d_free_texture(highlight);
			performanceMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(performanceBg);
	sf2d_free_texture(highlight);

	return 0;
}

int securityMenu()
{
	if (DARK == 1)
	{
		load_PNG(securityBg, "/3ds/Cyanogen3DS/system/settings/Dark/securityBg.png");
		load_PNG(highlight, "/3ds/Cyanogen3DS/system/settings/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(securityBg, securityBgPath);
		load_PNG(highlight, highlightPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, securityBg);
	setBilinearFilter(1, highlight);
	
	static SwkbdState swkbd;
	
	while (aptMainLoop())
	{
		hidScanInput();
        hidTouchRead(&touch);

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(securityBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsSecuirty[language][0]); 
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsSecuirty[language][1]); 
		sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsSecuirty[language][2]); 
		
		if (screenDisplay == 0)
		{
			digitalTime(352, 2, 0);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
		}
		
		if (cursor(0, 400, 58, 105))
		{	
			sf2d_draw_texture(highlight, 0, 56);
			sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsSecuirty[language][0]); 
			if (kDown & KEY_A)
			{
				if (fileExists("/3ds/Cyanogen3DS/system/settings/password.bin"))
					deleteFile("/3ds/Cyanogen3DS/system/settings/password.bin");
				else if (fileExists("/3ds/Cyanogen3DS/system/settings/pin.bin"))
					deleteFile("/3ds/Cyanogen3DS/system/settings/pin.bin");
				
				swkbdInit(&swkbd, SWKBD_TYPE_WESTERN, 2, 20);
				swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
				swkbdInputText(&swkbd, tempMessage, sizeof(tempMessage));
				FILE * password = fopen("system/settings/password.bin", "w");
				fprintf(password, "%s", tempMessage);
				fclose(password);
				return securityMenu();
			}
		}
		
		else if (cursor(0, 400, 106, 157))
		{	
			sf2d_draw_texture(highlight, 0, 105);
			sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsSecuirty[language][1]); 
			if (kDown & KEY_A)
			{
				if (fileExists("/3ds/Cyanogen3DS/system/settings/password.bin"))
					deleteFile("/3ds/Cyanogen3DS/system/settings/password.bin");
				else if (fileExists("/3ds/Cyanogen3DS/system/settings/pin.bin"))
					deleteFile("/3ds/Cyanogen3DS/system/settings/pin.bin");
				
				swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 4);
				swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_HIDE_DELAY);
				swkbdSetValidation(&swkbd, SWKBD_ANYTHING, 0, 0);
				swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
				swkbdInputText(&swkbd, tempPin, sizeof(tempPin));
				FILE * pin = fopen("system/settings/pin.bin", "w");
				fprintf(pin, "%s", tempPin);
				fclose(pin);
				return securityMenu();
			}
		}
		
		else if (cursor(0, 400, 158, 209))
		{	
			sf2d_draw_texture(highlight, 0, 157);
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsSecuirty[language][2]); 
			if (kDown & KEY_A)
			{
				if (fileExists("/3ds/Cyanogen3DS/system/settings/password.bin"))
					deleteFile("/3ds/Cyanogen3DS/system/settings/password.bin");
				else if (fileExists("/3ds/Cyanogen3DS/system/settings/pin.bin"))
					deleteFile("/3ds/Cyanogen3DS/system/settings/pin.bin");
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
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
		{
			sf2d_free_texture(securityBg);
			sf2d_free_texture(highlight);
			settingsMenu();
		}
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}

	sf2d_free_texture(securityBg);
	sf2d_free_texture(highlight);

	return 0;
}

int settingsHighlight(int style)
{
	u32 kDown = hidKeysDown();

	if (cursor(0, 198, 75, 133))
	{
		if (style == 1)
		{
			sf2d_draw_texture_scale(wifi_highlight, 0, 75, 0.9, 0.9);
			sftd_draw_textf(robotoS12, 43, 96, fontColor, 12, "%s", lang_settingsMain[language][0]);
		}	
		else
		{
			sf2d_draw_texture(wifi_highlight, 0, 87);
			sftd_draw_textf(robotoS12, 48, 106, fontColor, 12, "%s", lang_settingsMain[language][0]);
		}
		/*if (kDown & KEY_A)
		{
			settingsUnload();
		}*/
	}
	else if (cursor(0, 198, 134, 174))
	{
		if (style == 1)
		{
			sf2d_draw_texture_scale(display_highlight, 0, 115, 0.9, 0.9);
			sftd_draw_textf(robotoS12, 43, 143, fontColor, 12, "%s", lang_settingsMain[language][2]);
		}
		else
		{
			sf2d_draw_texture(display_highlight, 0, 135);
			sftd_draw_textf(robotoS12, 48, 153, fontColor, 12, "%s", lang_settingsMain[language][2]);
		}
		if (kDown & KEY_A)
		{
			settingsUnload();
			displayMenu();
		}
	}
	else if (cursor(0, 198, 175, 240))
	{
		if (style == 1)
		{
			sf2d_draw_texture_scale(developeroptions_highlight, 0, 163, 0.9, 0.9);
			sftd_draw_textf(robotoS12, 43, 192, fontColor, 12, "%s", lang_settingsMain[language][4]);
		}
		else
		{
			sf2d_draw_texture(developeroptions_highlight, 0, 183);
			sftd_draw_textf(robotoS12, 48, 202, fontColor, 12, "%s", lang_settingsMain[language][4]);
		}
		if (kDown & KEY_A)
		{
			settingsUnload();
			developerMenu();
		}
	}
	else if (cursor(203, 400, 75, 133))
	{
		if (style == 1)
		{
			sf2d_draw_texture_scale(security_highlight, 179, 75, 0.9, 0.9);
			sftd_draw_textf(robotoS12, 230, 96, fontColor, 12, "%s", lang_settingsMain[language][1]);
		}
		else
		{
			sf2d_draw_texture(security_highlight, 199, 87);
			sftd_draw_textf(robotoS12, 250, 106, fontColor, 12, "%s", lang_settingsMain[language][1]);
		}
		if (kDown & KEY_A)
		{
			settingsUnload();
			securityMenu();
		}
	}
	else if (cursor(203, 400, 134, 174))
	{
		if (style == 1)
		{
			sf2d_draw_texture_scale(performance_highlight, 183, 115, 0.9, 0.9);
			sftd_draw_textf(robotoS12, 230, 143, fontColor, 12, "%s", lang_settingsMain[language][3]);
		}
		else
		{
			sf2d_draw_texture(performance_highlight, 203, 135);
			sftd_draw_textf(robotoS12, 250, 153, fontColor, 12, "%s", lang_settingsMain[language][3]);
		}
		if (kDown & KEY_A)
		{
			settingsUnload();
			performanceMenu();
		}
	}
	else if (cursor(203, 400, 175, 240))
	{
		if (style == 1)
		{
			sf2d_draw_texture_scale(about_highlight, 183, 163, 0.9, 0.9);
			sftd_draw_textf(robotoS12, 230, 192, fontColor, 12, "%s", lang_settingsMain[language][5]);
		}
		else
		{	
			sf2d_draw_texture(about_highlight, 203, 183);
			sftd_draw_textf(robotoS12, 250, 202, fontColor, 12, "%s", lang_settingsMain[language][5]);
		}
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
	FILE * file = fopen(settingsFontColorPath, "r");
	fscanf(file, "%d %d %d", &SettingfontColor.r, &SettingfontColor.g, &SettingfontColor.b);
	fclose(file);
	
	if (DARK == 1)
	{
		load_PNG(settingsBg, "/3ds/Cyanogen3DS/system/settings/Dark/settingsBg.png");
		load_PNG(about_highlight, "/3ds/Cyanogen3DS/system/settings/Dark/about_highlight.png");
		load_PNG(display_highlight, "/3ds/Cyanogen3DS/system/settings/Dark/display_highlight.png");
		load_PNG(developeroptions_highlight, "/3ds/Cyanogen3DS/system/settings/Dark/developersoptions_highlight.png");
		load_PNG(performance_highlight, "/3ds/Cyanogen3DS/system/settings/Dark/performance_highlight.png");
		load_PNG(security_highlight, "/3ds/Cyanogen3DS/system/settings/Dark/security_highlight.png");
		load_PNG(wifi_highlight, "/3ds/Cyanogen3DS/system/settings/Dark/wifi_highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(settingsBg, settingsBgPath);
		load_PNG(about_highlight, aboutPath);
		load_PNG(display_highlight, themesPath);
		load_PNG(developeroptions_highlight, developerPath);
		load_PNG(performance_highlight, performancePath);
		load_PNG(security_highlight, securityPath);
		load_PNG(wifi_highlight, wifiPath);
		fontColor = RGBA8(SettingfontColor.r, SettingfontColor.g, SettingfontColor.b, 255);
	}
	
	setBilinearFilter(1, settingsBg);
	setBilinearFilter(1, about_highlight);
	setBilinearFilter(1, display_highlight);
	setBilinearFilter(1, developeroptions_highlight);
	setBilinearFilter(1, performance_highlight);
	setBilinearFilter(1, security_highlight);
	setBilinearFilter(1, wifi_highlight);
	
	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));
	
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		if (screenDisplay == 0)
		{
			sf2d_draw_texture(settingsBg, 0, 0);
		
			sftd_draw_textf(robotoS12, 48, 106, fontColor, 12, "%s", lang_settingsMain[language][0]);
			sftd_draw_textf(robotoS12, 48, 153, fontColor, 12, "%s", lang_settingsMain[language][2]);
			sftd_draw_textf(robotoS12, 48, 202, fontColor, 12, "%s", lang_settingsMain[language][4]);
			sftd_draw_textf(robotoS12, 250, 106, fontColor, 12, "%s", lang_settingsMain[language][1]);
			sftd_draw_textf(robotoS12, 250, 153, fontColor, 12, "%s", lang_settingsMain[language][3]);
			sftd_draw_textf(robotoS12, 250, 202, fontColor, 12, "%s", lang_settingsMain[language][5]);
			
			settingsHighlight(0);
			
			digitalTime(352, 2, 0);
			batteryStatus(300, 2, 0); 
			//androidQuickSettings();
		}
		
		else if (screenDisplay == 1)
		{
			sf2d_draw_texture_scale(settingsBg, 0, 0, 0.9, 0.9);
			
			sftd_draw_textf(robotoS12, 43, 96, fontColor, 12, "%s", lang_settingsMain[language][0]);
			sftd_draw_textf(robotoS12, 43, 143, fontColor, 12, "%s", lang_settingsMain[language][2]);
			sftd_draw_textf(robotoS12, 43, 192, fontColor, 12, "%s", lang_settingsMain[language][4]);
			sftd_draw_textf(robotoS12, 230, 96, fontColor, 12, "%s", lang_settingsMain[language][1]);
			sftd_draw_textf(robotoS12, 230, 143, fontColor, 12, "%s", lang_settingsMain[language][3]);
			sftd_draw_textf(robotoS12, 230, 192, fontColor, 12, "%s", lang_settingsMain[language][5]);
			
			settingsHighlight(1);
		}	
		
		cursorController();
		
		sf2d_end_frame();
		
		switchDisplayModeOn(2);
		
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
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
			appDrawer();
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}
	
	settingsUnload();
	
	return 0;
}
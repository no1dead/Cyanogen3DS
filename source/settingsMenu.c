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

int aboutMenu()
{
	if (DARK == 1)
	{
		load_PNG(aboutBg, "romfs:/Dark/aboutBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(aboutBg, "romfs:/aboutBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		fontColor = BLACK;
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
		load_PNG(developerBg, "romfs:/Dark/developerBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		load_PNG(onSwitch, "romfs:/onSwitch.png");
		load_PNG(offSwitch, "romfs:/offSwitch.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(developerBg, "romfs:/developerBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		load_PNG(onSwitch, "romfs:/onSwitch.png");
		load_PNG(offSwitch, "romfs:/offSwitch.png");
		fontColor = BLACK;
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
					load_PNG(developerBg, "romfs:/Dark/developerBg.png");
					load_PNG(highlight, "romfs:/Dark/highlight.png");
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
					load_PNG(developerBg, "romfs:/developerBg.png");
					load_PNG(highlight, "romfs:/highlight.png");
					fontColor = BLACK;
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
		load_PNG(displayBg, "romfs:/Dark/displayBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, "romfs:/displayBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		fontColor = BLACK;
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
			if (kDown & KEY_A)
			{
				sf2d_free_texture(displayBg);
				sf2d_free_texture(highlight);
				displayThemes();
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
		load_PNG(displayBg, "romfs:/Dark/displayBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, "romfs:/displayBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		fontColor = BLACK;
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

int displayIconPack()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "romfs:/Dark/displayBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, "romfs:/displayBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		fontColor = BLACK;
	}
	
	setBilinearFilter(1, displayBg);
	setBilinearFilter(1, highlight);

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(displayBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 20, 73, fontColor, 12, "Serie54");
		
		sftd_draw_textf(robotoS12, 20, 89, fontColor, 12, "Press 'x' to switch back to default");
		
		if (cursor(0, 480, 55, 105))
		{
			sf2d_draw_texture(highlight, 0, 55);
			sftd_draw_textf(robotoS12, 20, 73, fontColor, 12, "Serie54");
				
			if (kDown & KEY_A)
			{
				strcpy(appDirPath, "/3ds/Cyanogen3DS/system/icons/Serie54");
				FILE * iconPackTxt = fopen("/3ds/Cyanogen3DS/system/settings/iconpack.bin", "w");
				fprintf(iconPackTxt,"%s", appDirPath);
				fclose(iconPackTxt);
				iconPackLoad();
				iconPackReload();
			}
		}
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0);
		//androidQuickSettings();
		cursorController();
		
		sf2d_end_frame();
		
		navbarControls(0);
		
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

void replaceAsset(char tempData[], char path[], char imgPath[], char redirectPath[])
{
	strcpy(tempData, path);
	strcat(tempData, imgPath); 
	strcpy(redirectPath, tempData);
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
	sf2d_free_texture(ic_launcher_apollo);
	sf2d_free_texture(ic_launcher_browser);
	sf2d_free_texture(ic_launcher_messenger);
	sf2d_free_texture(ic_launcher_settings);

	load_PNG(ic_launcher_apollo, apolloPath);
	load_PNG(ic_launcher_browser, browserPath);
	load_PNG(ic_launcher_messenger, messagesPath);
	load_PNG(ic_launcher_settings, settingsPath);
	
	displayIconPack();
}

int displayTime()
{
	if (DARK == 1)
	{
		load_PNG(displayBg, "romfs:/Dark/displayBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		load_PNG(onSwitch, "romfs:/onSwitch.png");
		load_PNG(offSwitch, "romfs:/offSwitch.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(displayBg, "romfs:/displayBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		load_PNG(onSwitch, "romfs:/onSwitch.png");
		load_PNG(offSwitch, "romfs:/offSwitch.png");
		fontColor = BLACK;
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
		load_PNG(performanceBg, "romfs:/Dark/performanceBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(performanceBg, "romfs:/performanceBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		fontColor = BLACK;
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
		load_PNG(performanceBg2, "romfs:/Dark/performanceBg2.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(performanceBg2, "romfs:/performanceBg2.png");
		load_PNG(highlight, "romfs:/highlight.png");
		fontColor = BLACK;
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
		sf2d_draw_rectangle(20, 86, ((((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) / (((u64) resource.totalClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) * 360) - 20, 10, TEAL);
		
		FSUSER_GetArchiveResource(&resource, SYSTEM_MEDIATYPE_CTR_NAND);
		sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "CTR NAND: %.1f MB", ((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0);
		sf2d_draw_rectangle(20, 134, 360, 10, RGBA8(206, 215, 219, 255));
		sf2d_draw_rectangle(20, 134, ((((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) / (((u64) resource.totalClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0) * 360) - 20, 10, TEAL);
		
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

int securityMenu()
{
	if (DARK == 1)
	{
		load_PNG(securityBg, "romfs:/Dark/securityBg.png");
		load_PNG(highlight, "romfs:/Dark/highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(securityBg, "romfs:/securityBg.png");
		load_PNG(highlight, "romfs:/highlight.png");
		fontColor = BLACK;
	}
	
	setBilinearFilter(1, securityBg);
	setBilinearFilter(1, highlight);
	
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
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0);
		//androidQuickSettings();
		
		if (cursor(0, 480, 58, 105))
		{	
			sf2d_draw_texture(highlight, 0, 56);
			sftd_draw_textf(robotoS12, 20, 68, fontColor, 12, "%s", lang_settingsSecuirty[language][0]); 
			if (kDown & KEY_A)
			{
				//if (fileExists("system/settings/password.bin", &sdmcArchive))
					//sceIoRemove("system/settings/password.bin");
				/*else*/ if (fileExists("system/settings/pin.bin"))
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
			sftd_draw_textf(robotoS12, 20, 116, fontColor, 12, "%s", lang_settingsSecuirty[language][1]); 
			if (kDown & KEY_A)
			{
				//if (fileExists("system/settings/password.bin", &sdmcArchive))
					//sceIoRemove("system/settings/password.bin");
				/*else*/ if (fileExists("system/settings/pin.bin"))
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
			sftd_draw_textf(robotoS12, 20, 168, fontColor, 12, "%s", lang_settingsSecuirty[language][2]); 
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

int settingsHighlight()
{
	u32 kDown = hidKeysDown();

	if (cursor(0, 198, 75, 133))
	{
		sf2d_draw_texture(wifi_highlight, 0, 87);
		sftd_draw_textf(robotoS12, 48, 106, fontColor, 12, "%s", lang_settingsMain[language][0]);
		/*if (kDown & KEY_A)
		{
			settingsUnload();
		}*/
	}
	else if (cursor(0, 198, 134, 174))
	{
		sf2d_draw_texture(display_highlight, 0, 135);
		sftd_draw_textf(robotoS12, 48, 153, fontColor, 12, "%s", lang_settingsMain[language][2]);
		if (kDown & KEY_A)
		{
			if (experimentalF == 1)
			{
				settingsUnload();
				displayMenu();
			}
		}
	}
	else if (cursor(0, 198, 175, 240))
	{
		sf2d_draw_texture(developeroptions_highlight, 0, 183);
		sftd_draw_textf(robotoS12, 48, 202, fontColor, 12, "%s", lang_settingsMain[language][4]);
		if (kDown & KEY_A)
		{
			settingsUnload();
			developerMenu();
		}
	}
	else if (cursor(203, 400, 75, 133))
	{
		sf2d_draw_texture(security_highlight, 199, 87);
		sftd_draw_textf(robotoS12, 250, 106, fontColor, 12, "%s", lang_settingsMain[language][1]);
		if (kDown & KEY_A)
		{
			if (experimentalF == 1)
			{
				settingsUnload();
				securityMenu();
			}
		}
	}
	else if (cursor(203, 400, 134, 174))
	{
		sf2d_draw_texture(performance_highlight, 203, 135);
		sftd_draw_textf(robotoS12, 250, 153, fontColor, 12, "%s", lang_settingsMain[language][3]);
		if (kDown & KEY_A)
		{
			settingsUnload();
			performanceMenu();
		}
	}
	else if (cursor(203, 400, 175, 240))
	{
		sf2d_draw_texture(about_highlight, 203, 183);
		sftd_draw_textf(robotoS12, 250, 202, fontColor, 12, "%s", lang_settingsMain[language][5]);
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
	if (DARK == 1)
	{
		load_PNG(settingsBg, "romfs:/Dark/settingsBg.png");
		load_PNG(about_highlight, "romfs:/Dark/about_highlight.png");
		load_PNG(display_highlight, "romfs:/Dark/display_highlight.png");
		load_PNG(developeroptions_highlight, "romfs:/Dark/developersoptions_highlight.png");
		load_PNG(performance_highlight, "romfs:/Dark/performance_highlight.png");
		load_PNG(security_highlight, "romfs:/Dark/security_highlight.png");
		load_PNG(wifi_highlight, "romfs:/Dark/wifi_highlight.png");
		fontColor = LITEGRAY;
	}
	else
	{
		load_PNG(settingsBg, "romfs:/settingsBg.png");
		load_PNG(about_highlight, "romfs:/about_highlight.png");
		load_PNG(display_highlight, "romfs:/display_highlight.png");
		load_PNG(developeroptions_highlight, "romfs:/developersoptions_highlight.png");
		load_PNG(performance_highlight, "romfs:/performance_highlight.png");
		load_PNG(security_highlight, "romfs:/security_highlight.png");
		load_PNG(wifi_highlight, "romfs:/wifi_highlight.png");
		fontColor = BLACK;
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
		
		sf2d_draw_texture(settingsBg, 0, 0);
		
		sftd_draw_textf(robotoS12, 48, 106, fontColor, 12, "%s", lang_settingsMain[language][0]);
		sftd_draw_textf(robotoS12, 48, 153, fontColor, 12, "%s", lang_settingsMain[language][2]);
		sftd_draw_textf(robotoS12, 48, 202, fontColor, 12, "%s", lang_settingsMain[language][4]);
		sftd_draw_textf(robotoS12, 250, 106, fontColor, 12, "%s", lang_settingsMain[language][1]);
		sftd_draw_textf(robotoS12, 250, 153, fontColor, 12, "%s", lang_settingsMain[language][3]);
		sftd_draw_textf(robotoS12, 250, 202, fontColor, 12, "%s", lang_settingsMain[language][5]);
		
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
		
		if (touch(44, 119, 201, 240) && (kDown & KEY_TOUCH))
			appDrawer();
		
		captureScreenshot();
		
		sf2d_swapbuffers();	
	}
	
	settingsUnload();
	
	return 0;
}
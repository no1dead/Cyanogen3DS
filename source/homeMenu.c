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
#include "sound.h"
#include "utils.h"

int notif_y = -240;
int yPos1 = -240;
int yPos2 = -240;
int yLine1 = -240;
int yLine2 = -240;

struct timeAndBatteryStatusFontColor fontColorTime;
struct clockWidgetFontColor lFontColor;

void cursorController()
{
	hidScanInput();

    kDown = hidKeysDown();
    kHeld = hidKeysHeld();
    kUp = hidKeysUp();

    hidTouchRead(&touch);

    if(kHeld & (KEY_LEFT | KEY_CPAD_LEFT | KEY_CSTICK_LEFT))
        if(cursorX > 0)
            cursorX--;

    if(kHeld & (KEY_RIGHT | KEY_CPAD_RIGHT | KEY_CSTICK_RIGHT))
        if(cursorX < 380)
            cursorX++;

    if(kHeld & (KEY_DOWN | KEY_CPAD_DOWN | KEY_CSTICK_DOWN))
        if(cursorY < 220)
            cursorY++;

    if(kHeld & (KEY_UP | KEY_CPAD_UP | KEY_CSTICK_UP))
        if(cursorY > 0)
			cursorY--;
		
	sf2d_draw_texture(cursor, cursorX, cursorY);
}

int batteryStatus(int x, int y, int style)
{
	u32 wifiStatus = 0;
	
	u8 batteryPercent;
	PTMU_GetBatteryLevel(&batteryPercent);
	
	u8 batteryState; //boolean that represnets charging state
	PTMU_GetBatteryChargeState(&batteryState);

	int batt = (u32)batteryPercent * 20;
	
	if(batt == 20)
		sf2d_draw_texture(_20, x, y);	
	else if(batt == 40)
		sf2d_draw_texture(_40, x, y);
	else if(batt == 60)
		sf2d_draw_texture(_60, x, y);
	else if(batt == 80)
		sf2d_draw_texture(_80, x, y);
	else if(batt == 100)
		sf2d_draw_texture(_100, x, y);
	
	if (batteryState == 1) 
	{
		sf2d_draw_texture(_charge, x+1, y);
	}
	
	if (style == 0)
		sftd_draw_textf(robotoS12, x+16, y, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 12, "%d%%", batt);
	else if (style == 1)
		sftd_draw_textf(robotoS12, x-35, y, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 12, "%d%%", batt);
		
	ACU_GetWifiStatus(&wifiStatus);
	int wifiStat = wifiStatus + osGetWifiStrength();
		
	if (style == 0)
	{
		if (wifiStat == 0)
			sf2d_draw_texture(wifiIcon0, x-26, y-1);
		else if (wifiStat == 1)
			sf2d_draw_texture(wifiIcon1, x-26, y-1);
		else if (wifiStat == 2)
			sf2d_draw_texture(wifiIcon2, x-26, y-1);
		else if (wifiStat == 3)
			sf2d_draw_texture(wifiIcon3, x-26, y-1);
		else 
			sf2d_draw_texture(wifiIconNull, x-26, y-1);
	}
	else if (style == 1)
	{
		if (wifiStat == 0)
			sf2d_draw_texture(wifiIcon0, 116, y+105);
		else if (wifiStat == 1)
			sf2d_draw_texture(wifiIcon1, 116, y+105);
		else if (wifiStat == 2)
			sf2d_draw_texture(wifiIcon2, 116, y+105);
		else if (wifiStat == 3)
			sf2d_draw_texture(wifiIcon3, 116, y+105);
		else 
			sf2d_draw_texture(wifiIconNull, 116, y+105);
	}
	
	return 0;
}

void appDrawerIcon(int type) //Draws the app drawer icon. Draws a different icon of the same size once hovered with the cursor.
{
	if (type == 0)
	{
		if (cursor(170, 210, 155, 200))
			sf2d_draw_texture(ic_allapps_pressed, 179, 168);
		else
			sf2d_draw_texture(ic_allapps, 179, 168);
	}
	else if (type == 1)
	{
		if (cursor(130, 170, 140, 200))
			sf2d_draw_texture(ic_allapps_pressed, 139, 158);
		else
			sf2d_draw_texture(ic_allapps, 139, 158);
	}
	
}

int navbarControls(int type)
{
	//hidKeysHeld returns information about which buttons have are held down in this frame
	u32 kHeld = hidKeysHeld();
	
	if(hidKeysDown()&KEY_TOUCH)
    {
		touchTimer = 0;
		firstTouch = touch;
    }
    if(hidKeysHeld()&KEY_TOUCH)
	{
		touchTimer++;
    }
	
	//Read the touch screen coordinates
	if (kHeld & KEY_TOUCH) 
	{
		hidTouchRead(&touch);
		touch_x = touch.px;
		touch_y = touch.py;
	}
	
	if (type == 0)
	{
		if (screenDisplay == 0)
			sf2d_start_frame(switchDisplay(screenDisplay - 1), GFX_LEFT);
		
		if touch(44, 119, 201, 240)
			sf2d_draw_texture(navbarHighlight, 51, 201);
		else
			sf2d_draw_texture(navbar, 30, 201);

		if touch(120, 195, 201, 240)
		{
			sf2d_draw_texture(navbarHighlight, 116, 201);
			if (kDown & KEY_TOUCH)
				home();
		}
		else
			sf2d_draw_texture(navbar, 30, 201);
	
		if touch(196, 271, 201, 240)
			sf2d_draw_texture(navbarHighlight, 181, 201);
		else
			sf2d_draw_texture(navbar, 30, 201);
		
		if (screenDisplay == 0)		
			sf2d_end_frame();
	}
	
	return 0;
}

void androidQuickSettings()
{
	if (kHeld & KEY_TOUCH) 
	{
		hidTouchRead(&touch);
		touch_x = touch.px;
		touch_y = touch.py;
	}

	int notif_up;
	int notif_down;
	int notif_enabled = 0;
	
	sf2d_draw_texture(quickSettings, 0, notif_y);
	
	batteryStatus(305, yPos2-5, 1);
	//sftd_draw_textf(robotoS10, 346, yPos2-5, RGBA8(255, 255, 255, 255), 10, "%.6s", getUsername);
	
	sftd_draw_textf(robotoS10, 115, yLine1, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 10, "%s", lang_quickSettings[language][0]);
	sftd_draw_textf(robotoS10, 245, yLine1, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 10, "%s", lang_quickSettings[language][2]);
	sftd_draw_textf(robotoS10, 170, yLine2, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 10, "%s", lang_quickSettings[language][4]);
	sftd_draw_textf(robotoS10, 20, yPos1+14, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 10, "%s", getDayOfWeek(0));
	sftd_draw_textf(robotoS10, 85, yPos1+14, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 10, "%s", getMonthOfYear(0));

	digitalTime(19, yPos1, 0);

	if ((kHeld & KEY_TOUCH) && (touch(0, 320, 0, 20))) 
	{
		notif_down = 1;
	}

	else if ((kHeld & KEY_TOUCH) && (touch.px >= 0 && touch.px <= 320 && touch.py >= 170) && (notif_y == 0))
	{
		notif_up = 1;
	}
			
	if (notif_down == 1 /*&& touch.py <= 10*/)
	{	
		if ((kHeld & KEY_TOUCH) && (touch_y >= 50))
		{
			notif_y = notif_y+4;
			yPos1 = yPos1+4;
			yPos2 = yPos2+4;
			yLine1 = yLine1+4;
			yLine2 = yLine2+4;
		}
		
		if (notif_y >= 0)
		{
			notif_y = 0;
		}
		
		if (yPos1 >= 10)
		{
			yPos1 = 10;
		}
		if (yPos2 >= 20)
		{
			yPos2 = 20;
		}
		if (yLine1 >= 155)
		{
			yLine1 = 155;
		}
		if (yLine2 >= 220)
		{
			yLine2 = 220;
			notif_enabled = 1;
		}
	}

	if (yLine2 >= 136 || notif_enabled == 1)
	{		
		if ((cursor(386, 414, 12, 38)) && (kDown & KEY_A))
		{	 
			notif_y = notif_y-240;
			yPos1 = yPos1-240;
			yPos2 = yPos2-240;
			yLine1 = yLine1-240;
			yLine2 = yLine2-240;
			settingsMenu();
		}
		
		if ((cursor(198, 240, 204, 258)) && (kDown & KEY_A))
		{
			notif_y = notif_y-240;
			yPos1 = yPos1-240;
			yPos2 = yPos2-240;
			yLine1 = yLine1-240;
			yLine2 = yLine2-240;
			lockScreen();
		}
	}
	
	if ((notif_down == 1) && (kDown & KEY_B))
	{
		notif_y = notif_y-240;
		yPos1 = yPos1-240;
		yPos2 = yPos2-240;
		yLine1 = yLine1-240;
		yLine2 = yLine2-240;
	}
	
	if (notif_up == 1)
	{				
		notif_enabled = 0;
		
		if ((kHeld & KEY_TOUCH) && (touch_y <= 50))
		{
			notif_y = notif_y-4;
			yPos1 = yPos1-4;
			yPos2 = yPos2-4;
			yLine1 = yLine1-4;
			yLine2 = yLine2-4;
		}
		
		if (notif_y <= -240)
		{	
			notif_y = -240;
			yPos1 = -240;
			yPos2 = -240;
			yLine1 = -240;
			yLine2 = -240;
		}
	}
}

int dayNightWidget()
{
	time_t unix_time = time(0);
	struct tm* time_struct = gmtime((const time_t*)&unix_time);
	int hours = time_struct->tm_hour;
	
	if (hrTime == 1)
	{
		if(hours == 0)
		{
			hours = 12;
		}
		else if(hours > 12)
		{
			hours = hours - 12;
		}
	}
	
	if (hours < 6)
		sf2d_draw_texture(dayWidget, 172, 70);
	else
		sf2d_draw_texture(nightWidget, 167, 70);
		
	digitalTime(155, 30, 1);
	sftd_draw_textf(robotoS10, 145, 90, RGBA8(lFontColor.r, lFontColor.g, lFontColor.b, 255), 10, "%s", getDayOfWeek(1));
	sftd_draw_textf(robotoS10, 235, 90, RGBA8(lFontColor.r, lFontColor.g, lFontColor.b, 255), 10, "%s", getMonthOfYear(0));
	
	return 0;
}

int switchDisplayModeOn(int app)
{
	if (screenDisplay == 1)
	{
		sf2d_start_frame(switchDisplay(0), GFX_LEFT);
		sf2d_draw_texture(background, 0, 0);
		
		if (app == 0 || app == 1)
			dayNightWidget();
			
		else if (app == 2)
			sf2d_draw_texture_scale(ic_launcher_settings, 170, 90, 1.4, 1.4);
		
		digitalTime(352, 2, 0); //Displays digital time
		batteryStatus(300, 2, 0); //Displays battery status
		//androidQuickSettings();
		sf2d_end_frame();
	}
	
	return 0;
}

int home()
{
	firstBoot = setFileDefaultsInt("/3ds/Cyanogen3DS/system/settings/boot.bin", 1, firstBoot);
	widgetActivator = setFileDefaultsInt("/3ds/Cyanogen3DS/system/widget/widgetActivator.bin", 1, widgetActivator);

	FILE * file = fopen(clockWidgetFontColorPath, "r");
	fscanf(file, "%d %d %d", &lFontColor.r, &lFontColor.g, &lFontColor.b);
	fclose(file);
	
	file = fopen(timeAndBatteryFontColorPath, "r");
	fscanf(file, "%d %d %d", &fontColorTime.r, &fontColorTime.g, &fontColorTime.b);
	fclose(file);
	
	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));
	
	setBilinearFilter(1, ic_allapps);
	setBilinearFilter(1, ic_allapps_pressed);
	
	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		if (hidKeysDown() & KEY_START)
			break;

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		//hidKeysUp returns information about which buttons have been just released
		//u32 kUp = hidKeysUp();

		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(background, 0, 0);
		
		if (screenDisplay == 0)
		{
			if (cursor(44, 89, 155, 200))
				sf2d_draw_texture_scale(ic_launcher_browser, 44, 150, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_browser, 49, 155);
			if (cursor(109, 154, 155, 200))
				sf2d_draw_texture_scale(ic_launcher_messenger, 109, 150, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_messenger, 114, 155);
			if (cursor(236, 281, 155, 200))
				sf2d_draw_texture_scale(ic_launcher_apollo, 236, 150, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_apollo, 241, 155);
			if (cursor(301, 346, 155, 200))
				sf2d_draw_texture_scale(ic_launcher_settings, 301, 150, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_settings, 306, 155);
	
			appDrawerIcon(screenDisplay);
			
			if (widgetActivator == 1)
				dayNightWidget();
			digitalTime(352, 2, 0); //Displays digital time
			batteryStatus(300, 2, 0); //Displays battery status
			//androidQuickSettings();
		}
		
		else if (screenDisplay == 1)
		{
			if (cursor(4, 49, 140, 200))
				sf2d_draw_texture_scale(ic_launcher_browser, 4, 140, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_browser, 9, 140);
			if (cursor(69, 114, 140, 200))
				sf2d_draw_texture_scale(ic_launcher_messenger, 69, 140, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_messenger, 74, 140);
			if (cursor(196, 241, 140, 200))
				sf2d_draw_texture_scale(ic_launcher_apollo, 196, 140, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_apollo, 201, 140);
			if (cursor(261, 306, 140, 200))
				sf2d_draw_texture_scale(ic_launcher_settings, 261, 140, 1.1, 1.1);
			else
				sf2d_draw_texture(ic_launcher_settings, 266, 140);
	
			appDrawerIcon(screenDisplay);
		}
		
		if (firstBoot!= 0)
		{
			sf2d_draw_rectangle(0, 0, 400, 240, RGBA8(0, 0, 0, 100));
			sf2d_draw_texture(welcome, 0, 0);
			
			sftd_draw_textf(robotoS18, 10, 10, RGBA8(255, 255, 255, 255), 18, "%s", lang_welcome[language][0]);
			
			sftd_draw_textf(robotoS18, 10, 35, RGBA8(255, 255, 255, 255), 18, "%s", lang_welcome[language][1]);
			
			sftd_draw_textf(robotoS18, 10, 60, RGBA8(255, 255, 255, 255), 18, "%s", lang_welcome[language][2]);
			
			sftd_draw_textf(robotoS18, 330, 90, RGBA8(255, 255, 255, 255), 18, "%s", lang_welcome[language][3]);
		}
		
		cursorController();
		
		if (firstBoot!= 0)
		{
			if (cursor(330, 400, 90, 115) && (kDown & KEY_A))
			{
				FILE * firstBootTxt = fopen("/3ds/Cyanogen3DS/system/settings/boot.bin", "w"); 
				fprintf(firstBootTxt, "0");
				fclose(firstBootTxt);
				sf2d_free_texture(welcome);
				home();
			}
		}
		
		sf2d_end_frame();
		
		switchDisplayModeOn(0);
		
		navbarControls(0); //Displays navbar
		
		if ((cursor(170, 210, 158, 200)) && (kDown & KEY_A))
		{
			appDrawer(); //Opens app drawer
		}
		
		if ((cursor(306, 351, 155, 200)) && (kDown & KEY_A))
		{
			settingsMenu(); //Opens settings menu
		}
		
		if (kDown & KEY_Y)
			powerMenu(); //Opens power menu
		
		if (kDown & KEY_L)
		{
			//audio_load("system/media/audio/ui/lock.bin");
			lockScreen(); //Takes you to lock screen
		}
		
		captureScreenshot();

		// Flush and swap framebuffers
		sf2d_swapbuffers();
	}
	
	return 0;
}

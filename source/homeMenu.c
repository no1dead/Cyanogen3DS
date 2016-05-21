#include "appDrawer.h"
#include "clock.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "language.h"
#include "lockScreen.h"
#include "main.h"
#include "powerMenu.h"
#include "settingsMenu.h"
#include "sound.h"
#include "utils.h"

int notif_y = -240;
int yPos1 = -240;
int yPos2 = -240;
int yLine1 = -240;
int yLine2 = -240;

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
		sftd_draw_textf(robotoS12, x+16, y, RGBA8(255, 255, 255, 255), 12, "%d%%", batt);
	else if (style == 1)
		sftd_draw_textf(robotoS12, x-35, y, RGBA8(255, 255, 255, 255), 12, "%d%%", batt);
		
	ACU_GetWifiStatus(&wifiStatus);
	
	if(wifiStatus)
	{
		if (style == 0)
			sf2d_draw_texture(wifiIconFull, x-26, y-1);
		else if (style == 1)
			sf2d_draw_texture(wifiIconFull, 116, y+105);
	}
	else
	{
		if (style == 0)
			sf2d_draw_texture(wifiIconNull, x-26, y-1);
		else if (style == 1)
			sf2d_draw_texture(wifiIconNull, 116, y+105);
	}
	
	return 0;
}

void appDrawerIcon() //Draws the app drawer icon. Draws a different icon of the same size once hovered with the cursor.
{
	if (cursor(170, 210, 155, 200))
		sf2d_draw_texture(ic_allapps_pressed, 179, 168);
	
	else
		sf2d_draw_texture(ic_allapps, 179, 168);
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
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		
		if (touch.px  >= 44 && touch.px  <= 119 && touch.py >= 201 && touch.py <= 240)
			sf2d_draw_texture(backicon, 30, 201);
		else
			sf2d_draw_texture(navbar, 30, 201);

		if (touch.px  >= 120 && touch.px  <= 195 && touch.py >= 201 && touch.py <= 240)
		{
			sf2d_draw_texture(homeicon, 30, 201);
			if (kDown & KEY_TOUCH)
				home();
		}
		else
			sf2d_draw_texture(navbar, 30, 201);
	
		if (touch.px  >= 196 && touch.px  <= 271 && touch.py >= 201 && touch.py <= 240)
			sf2d_draw_texture(multicon, 30, 201);
		else
			sf2d_draw_texture(navbar, 30, 201);
			
		sf2d_end_frame();
	}
	
	return 0;
}

void androidQuickSettings()
{
	//u32 kDown = hidKeysDown();
	//u32 kHeld = hidKeysHeld();

	int notif_up;
	int notif_down;
	
	sf2d_draw_texture(quickSettings, 0, notif_y);
	
	batteryStatus(305, yPos2-5, 1);
	//sftd_draw_textf(robotoS10, 346, yPos2-5, RGBA8(255, 255, 255, 255), 10, "%.6s", getUsername);
	
	sftd_draw_textf(robotoS10, 115, yLine1, RGBA8(255, 255, 255, 255), 10, "%s", lang_quickSettings[language][0]);
	sftd_draw_textf(robotoS10, 245, yLine1, RGBA8(255, 255, 255, 255), 10, "%s", lang_quickSettings[language][2]);
	sftd_draw_textf(robotoS10, 170, yLine2, RGBA8(255, 255, 255, 255), 10, "%s", lang_quickSettings[language][4]);

	digitalTime(10, yPos1);
	getMonthOfYear(25, yPos1+14, 10);

	if ((kHeld & KEY_A) && (cursor(0, 400, 0, 20))) 
	{
		notif_down = 1;
	}

	else if ((kHeld & KEY_A) && (cursorX >= 0 && cursorX <= 480 && cursorY >= 250) && (notif_y == 0))
	{
		notif_up = 1;
	}
			
	if (notif_down == 1 && cursorY <= 10)
	{	
		if ((kHeld & KEY_A) && (kHeld & KEY_DOWN))
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
		}
	}

	if (yLine2 >= 136)
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
		if ((kHeld & KEY_A) && (kHeld & KEY_UP))
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
	u64 lastTimeInSeconds = 0;
	
	if(lastTimeInSeconds == 0) 
	{
		lastTimeInSeconds = osGetTime() / 1000; //get on boot.
	}
	u64 timeInSeconds = osGetTime() / 1000;

	lastTimeInSeconds = timeInSeconds;
	
	u64 convert = ( (70*365+17) * 86400LLU );
	time_t now = timeInSeconds- convert;
	struct tm *ts = localtime(&now);

	int hours = ts->tm_hour;
	int minutes = ts->tm_min;
	
	if (hours < 6)
		sf2d_draw_texture(dayWidget, 172, 70);
	else
		sf2d_draw_texture(nightWidget, 167, 70);
		
	sftd_draw_textf(robotoS30, 152, 30, RGBA8(255, 255, 255, 255), 34, "%2d : %02d", hours, minutes);
	getDayOfWeek(155, 90, 10);
	getMonthOfYear(235, 90, 10);
	
	return 0;
}

int home()
{
	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));
	
	load_PNG(ic_allapps, "romfs:/ic_allapps.png");
	load_PNG(ic_allapps_pressed, "romfs:/ic_allapps_pressed.png");
	load_PNG(ic_launcher_browser, "romfs:/ic_launcher_browser.png");
	load_PNG(ic_launcher_messenger, "romfs:/ic_launcher_messenger.png");
	load_PNG(ic_launcher_apollo, "romfs:/ic_launcher_apollo.png");
	load_PNG(ic_launcher_settings, "romfs:/ic_launcher_settings.png");
	
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

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(background, 0, 0);
		
		sf2d_draw_texture(ic_launcher_browser, 49, 155);
		sf2d_draw_texture(ic_launcher_messenger, 114, 155);
		sf2d_draw_texture(ic_launcher_apollo, 241, 155);
		sf2d_draw_texture(ic_launcher_settings, 306, 155);
		appDrawerIcon();

		dayNightWidget();
		
		digitalTime(343, 2); //Displays digital time
		batteryStatus(300, 2, 0); //Displays battery status
		androidQuickSettings();
		cursorController();
		
		sf2d_end_frame();
		navbarControls(0); //Displays navbar
		
		if ((cursor(170, 210, 158, 200)) && (kDown & KEY_A))
		{
			audioPlay(&KeypressStandard, false);
			sf2d_free_texture(ic_allapps);
			sf2d_free_texture(ic_allapps_pressed);
			appDrawer(); //Opens app drawer
		}
		
		if ((cursor(306, 351, 155, 200)) && (kDown & KEY_A))
		{
			sf2d_free_texture(ic_allapps);
			sf2d_free_texture(ic_allapps_pressed);
			settingsMenu(); //Opens settings menu
		}
		
		if (kDown & KEY_Y)
			powerMenu(); //Opens power menu
		
		if (kDown & KEY_L)
			lockScreen(); //Takes you to lock screen

		// Flush and swap framebuffers
		sf2d_swapbuffers();
	}
	
	sf2d_free_texture(ic_allapps);
	sf2d_free_texture(ic_allapps_pressed);
	
	return 0;
}

#include "clock.h"
#include "homeMenu.h"
#include "lockScreen.h"
#include "settingsMenu.h"
#include "utils.h"

int lockScreen()
{
	load_PNG(lockscreenBg, "romfs:/lockscreenBg.png");

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
	
	sf2d_set_clear_color(RGBA8(0, 0, 0, 0));

	while (1)
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(switchDisplay(screenDisplay), GFX_LEFT);
		
		sf2d_draw_texture(background, 0, 0);
		sf2d_draw_texture(lockscreenBg, 0, 0);

		sftd_draw_textf(robotoS30, 152, 30, RGBA8(255, 255, 255, 255), 34, "%2d : %02d", hours, minutes);
		sftd_draw_textf(robotoS10, 150, 90, RGBA8(255, 255, 255, 255), 10, "%s", getDayOfWeek(0));
		sftd_draw_textf(robotoS10, 215, 90, RGBA8(255, 255, 255, 255), 10, "%s", getMonthOfYear(0));
		
		digitalTime(343, 2);
		batteryStatus(300, 2, 0); 
		cursorController();
		
		sf2d_end_frame();
		
		if ((cursorX  >= 160 && cursorX  <= 235 && cursorY >= 210 && cursorY <= 240) && (kDown & KEY_A))
		{	
			sf2d_free_texture(lockscreenBg);
			return 1;
		}
			
		sf2d_swapbuffers();
	}
	
	sf2d_free_texture(lockscreenBg);
	
	return 0;
}

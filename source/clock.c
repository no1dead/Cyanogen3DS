#include "clock.h"
#include "homeMenu.h"

void digitalTime(int x, int y)
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
	
	sftd_draw_textf(roboto, x+10, y, RGBA8(255, 255, 255, 255), 12, "%2d:%02d", hours, minutes);

    if (hours > 12)
		sftd_draw_textf(roboto, x+30, y+2, RGBA8(255, 255, 255, 255), 10, "AM");
	else 
		sftd_draw_textf(roboto, x+30, y+2, RGBA8(255, 255, 255, 255), 10, "PM");
    if (hours > 12) 
		hours -= 12;
}

void getMonthOfYear(int x, int y, int size)
{
	u64 lastTimeInSeconds = 0;
	
	static const char months[12][16] =
	{
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
	
	if(lastTimeInSeconds == 0) 
	{
		lastTimeInSeconds = osGetTime() / 1000; //get on boot.
	}
	u64 timeInSeconds = osGetTime() / 1000;

	lastTimeInSeconds = timeInSeconds;
	
	u64 convert = ( (70*365+17) * 86400LLU );
	time_t now = timeInSeconds- convert;
	struct tm *ts = localtime(&now);
	int month = ts->tm_mon;
	int day = ts->tm_mday;
	
    sftd_draw_textf(roboto, x, y, RGBA8(255, 255, 255, 255), size, "%d %s", day, months[month]);
}

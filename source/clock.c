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
	
	sftd_draw_textf(robotoS12, x+10, y, RGBA8(255, 255, 255, 255), 12, "%2d:%02d", hours, minutes);

    if (hours > 12)
		sftd_draw_textf(robotoS10, x+39, y+2, RGBA8(255, 255, 255, 255), 10, "AM");
	else 
		sftd_draw_textf(robotoS10, x+39, y+2, RGBA8(255, 255, 255, 255), 10, "PM");
    if (hours > 12) 
		hours -= 12;
}


void getDayOfWeek(int x, int y, int size)
{
	//static const char days[7][16] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	
	time_t unixTime = time(NULL);
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);
	int day = timeStruct->tm_mday;
	
    sftd_draw_textf(robotoS10, x, y, RGBA8(255, 255, 255, 255), size, "%d", day);
}

void getMonthOfYear(int x, int y, int size)
{
	static const char months[12][16] =
	{
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
	
	time_t unixTime = time(NULL);
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);
	int month = timeStruct->tm_mon;
	
    sftd_draw_textf(robotoS10, x, y, RGBA8(255, 255, 255, 255), size, "%s", months[month]);
}

#include "clock.h"
#include "homeMenu.h"
#include "settingsMenu.h"

struct timeAndBatteryStatusFontColor fontColorTime;
struct clockWidgetFontColor lFontColor;

void digitalTime(int x, int y, int style)
{
	time_t unix_time = time(0);
	struct tm* time_struct = gmtime((const time_t*)&unix_time);
	int hours = time_struct->tm_hour;
	int minutes = time_struct->tm_min;
	bool amOrPm = false;
	
	if (hrTime == 0)
	{
		if(hours < 12)
			amOrPm = true;
		if(hours == 0)
		{
			hours = 12;
		}
		else if(hours > 12)
		{
			hours = hours - 12;
		}
	}
	
	if (style == 0)
	{
		if (hrTime == 0)
			sftd_draw_textf(robotoS12, x, y, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 12, "%2i:%02i", hours, minutes);
		else
			sftd_draw_textf(robotoS12, x+7, y, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 12, "%2i:%02i", hours, minutes);
	}
		
	else if (style == 1)
	{
		if (hrTime == 0)
			sftd_draw_textf(robotoS30, x+4, y, RGBA8(lFontColor.r, lFontColor.g, lFontColor.b, 255), 34, "%2i:%02i", hours, minutes);
		else
			sftd_draw_textf(robotoS30, x+1, y, RGBA8(lFontColor.r, lFontColor.g, lFontColor.b, 255), 34, "%2i:%02i", hours, minutes);
	}
	
	if ((hrTime == 0) && (style == 0))
	{
		if (amOrPm)
			sftd_draw_textf(robotoS10, x+30, y+2, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 10, "AM");
		else 
			sftd_draw_textf(robotoS10, x+30, y+2, RGBA8(fontColorTime.r, fontColorTime.g, fontColorTime.b, 255), 10, "PM");
	}
}

char * getDayOfWeek(int type)
{
	static const char days[7][16] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	
	time_t unixTime = time(NULL);
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);
	
	static char buffer[16];
	sprintf(buffer, "%s", days[timeStruct->tm_wday]);
    
    if(type == 1)
        buffer[3] = 0;
	
    return buffer;
}

char * getMonthOfYear(int type)
{
	static const char months[12][16] =
	{
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
	
	time_t unixTime = time(NULL);
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);
	int day = timeStruct->tm_mday;
	
	static char buffer[16];
	
	if (type == 0)
		sprintf(buffer, "%d %s", day, months[timeStruct->tm_mon]);
	else
		sprintf(buffer, "%s", months[timeStruct->tm_mon]);
	
	if (type == 1)
		buffer[3] = 0;
	
	return buffer;
}

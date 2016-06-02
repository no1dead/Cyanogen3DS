#include "clock.h"
#include "homeMenu.h"
#include "settingsMenu.h"

void digitalTime(int x, int y)
{
	time_t unix_time = time(0);
	struct tm* time_struct = gmtime((const time_t*)&unix_time);
	int hours = time_struct->tm_hour;
	int minutes = time_struct->tm_min;
	
		sftd_draw_textf(robotoS12, x+10, y, RGBA8(255, 255, 255, 255), 12, "%2d:%02d", hours, minutes);
		
	if(hours == 0)
	{
		hours = 12;
	}
	if (hours > 12) 
		hours -= 12;	
		
    if (hours > 12)
		sftd_draw_textf(robotoS10, x+39, y+2, RGBA8(255, 255, 255, 255), 10, "AM");
	else 
		sftd_draw_textf(robotoS10, x+39, y+2, RGBA8(255, 255, 255, 255), 10, "PM");
	
	//if (hrTime == 1)
	//{
	//}
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

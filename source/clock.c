#include "clock.h"
#include "homeMenu.h"

void digitalTime(int x, int y)
{
	bool hour24 = false; //Until I add an option this will be default
	
	struct tm *ts = localtime(&now);

	int hours = ts->tm_hour;
	int minutes = ts->tm_min;

    	char * state;

	

	sftd_draw_textf(roboto, x, y, RGBA8(255, 255, 255, 255), 12, "%2d:%02d", hours, minutes);
	
	if (hour24) state = "";
  	else 
  	{
        	if (hours > 12)
			sftd_draw_textf(roboto, x+30, y+2, RGBA8(255, 255, 255, 255), 10, "PM");
		else 
			sftd_draw_textf(roboto, x+30, y+2, RGBA8(255, 255, 255, 255), 10, "AM");
        	if (hour > 12) 
        		hour -= 12;
    	}
}

void getMonthOfYear(int x, int y, int size)
{
	static const char months[12][16] =
	{
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
       
	struct tm *ts = localtime(&now);
	int month = ts->tm_mon;
	int day = ts->tm_mday;
	
    sftd_draw_textf(roboto, x, y, RGBA8(255, 255, 255, 255), size, "%d %s", day, months[month]);
}

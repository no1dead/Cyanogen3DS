#pragma once

#include <3ds.h>
#include <stdio.h>
#include <time.h>

char clockWidgetFontColorPath[200];

struct clockWidgetFontColor 
{
   int	r;
   int	g;
   int	b;
};

void digitalTime(int x, int y, int style);
char * getDayOfWeek(int type);
char * getMonthOfYear(int type);
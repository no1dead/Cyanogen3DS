#include "boot.h"
#include "fileManager.h"
#include "homeMenu.h"
#include "utils.h"
#include "language.h"
#include "lockScreen.h"
#include "settingsMenu.h"

/*
	This part of the source includes all the first time boot stuff, such as boot animation and language prompt during startup.
*/

int bootAnimation()
{
	int currentFrame = 0, i = 0;
	
	bootAnimActivator = setFileDefaultsInt("/3ds/Cyanogen3DS/system/boot/bootAnimActivator.bin", 0, bootAnimActivator);
	firstBoot = setFileDefaultsInt("/3ds/Cyanogen3DS/system/settings/boot.bin", 1, firstBoot);
	
	if (bootAnimActivator != 1)
	{
		if (firstBoot == 1)
			home();
		else 
		{
			sf2d_free_texture(welcome);
			lockScreen();
			home();
		}
	}
	
	load_PNG(bootAnim[0], "/3ds/Cyanogen3DS/system/boot/part1/boot0.png");
	load_PNG(bootAnim[1], "/3ds/Cyanogen3DS/system/boot/part1/boot1.png");
	load_PNG(bootAnim[2], "/3ds/Cyanogen3DS/system/boot/part1/boot2.png");
	load_PNG(bootAnim[3], "/3ds/Cyanogen3DS/system/boot/part1/boot3.png");
	load_PNG(bootAnim[4], "/3ds/Cyanogen3DS/system/boot/part1/boot4.png");
	load_PNG(bootAnim[5], "/3ds/Cyanogen3DS/system/boot/part1/boot5.png");
	load_PNG(bootAnim[6], "/3ds/Cyanogen3DS/system/boot/part1/boot6.png");
	load_PNG(bootAnim[7], "/3ds/Cyanogen3DS/system/boot/part1/boot7.png");
	load_PNG(bootAnim[8], "/3ds/Cyanogen3DS/system/boot/part1/boot8.png");
	load_PNG(bootAnim[9], "/3ds/Cyanogen3DS/system/boot/part1/boot9.png");
	load_PNG(bootAnim[10], "/3ds/Cyanogen3DS/system/boot/part1/boot10.png");
	load_PNG(bootAnim[11], "/3ds/Cyanogen3DS/system/boot/part1/boot11.png");
	load_PNG(bootAnim[12], "/3ds/Cyanogen3DS/system/boot/part1/boot12.png");
	
	setBilinearFilter(1, bootAnim[0]);
	setBilinearFilter(1, bootAnim[1]);
	setBilinearFilter(1, bootAnim[2]);
	setBilinearFilter(1, bootAnim[3]);
	setBilinearFilter(1, bootAnim[4]);
	setBilinearFilter(1, bootAnim[5]);
	setBilinearFilter(1, bootAnim[6]);
	setBilinearFilter(1, bootAnim[7]);
	setBilinearFilter(1, bootAnim[8]);
	setBilinearFilter(1, bootAnim[9]);
	setBilinearFilter(1, bootAnim[10]);
	setBilinearFilter(1, bootAnim[11]);
	setBilinearFilter(1, bootAnim[12]);
	
	while (aptMainLoop())
	{
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(bootAnim[currentFrame], 55, -25);
		sf2d_end_frame();
		sf2d_swapbuffers();	
		sleepThread(65 * 1);
   
		currentFrame++;
		if(currentFrame > 12)
		{
			currentFrame = 0;
			i++;
		}
		
		if (i > 21)
		{
			for (i = 0; i <=12; i++)
			{
				sf2d_free_texture(bootAnim[i]);
			}
			
			if (firstBoot == 1)
				home();
			else 
			{
				sf2d_free_texture(welcome);
				lockScreen();
				home();
			}
		}
	}

	return 0;
}

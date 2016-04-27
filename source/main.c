#include "main.h"
#include "homeMenu.h"

int main(int argc, char **argv)
{
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	sf2d_set_vblank_wait(0);
	romfsInit();

	// Font loading
	sftd_init();
	ptmuInit();

	roboto = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size); //Loads font


	// Load images from RomFS, and tile them
	load_PNG(background, "romfs:/background.png", SF2D_PLACE_RAM);
	load_PNG(cursor, "romfs:/cursor.png", SF2D_PLACE_RAM);

	load_PNG(quickSettings, "romfs:/quickSettings.png", SF2D_PLACE_RAM);

	load_PNG(navbar, "romfs:/navbar.png", SF2D_PLACE_RAM);
	load_PNG(backicon, "romfs:/backicon.png", SF2D_PLACE_RAM);
	load_PNG(homeicon, "romfs:/homeicon.png", SF2D_PLACE_RAM);
	load_PNG(multicon, "romfs:/multicon.png", SF2D_PLACE_RAM);

	load_PNG(dayWidget, "romfs:/day.png", SF2D_PLACE_RAM);
	load_PNG(nightWidget, "romfs:/night.png", SF2D_PLACE_RAM);

	load_PNG(_100, "romfs:/100.png", SF2D_PLACE_RAM);
		
	// Main loop
	while (aptMainLoop())
	{
		home();
		break;
	}

	sftd_fini();
	sf2d_fini();
	romfsExit();
	ptmuExit();
	
	return 0;
}

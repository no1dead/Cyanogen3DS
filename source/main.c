#include "main.h"
#include "homeMenu.h"
#include "settingsMenu.h"
#include "sound.h"
#include "utils.h"

void cleanUp() 
{
	sftd_fini();
	sf2d_fini();
	romfsExit();
	cfguExit();
	ptmuExit();
	acExit();
	csndExit();
}

int main(int argc, char **argv)
{
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0, 0, 0, 255));
	sf2d_set_vblank_wait(0);
	romfsInit();
	cfguInit();
	acInit();
	csndInit();

	// Font loading
	sftd_init();
	ptmuInit();

	if ((getModel() == 2) || (getModel() == 4))
		osSetSpeedupEnable(true); //Enable N3DS speedup

	robotoS10 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);
	robotoS12 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);
	robotoS18 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);
	robotoS30 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);

	// Load textures from RomFS
	load_PNG(background, "romfs:/background.png");
	load_PNG(cursor, "romfs:/cursor.png");
	load_PNG(quickSettings, "romfs:/quickSettings.png");
	load_PNG(navbar, "romfs:/navbar.png");
	load_PNG(backicon, "romfs:/backicon.png");
	load_PNG(homeicon, "romfs:/homeicon.png");
	load_PNG(multicon, "romfs:/multicon.png");
	load_PNG(dayWidget, "romfs:/day.png");
	load_PNG(nightWidget, "romfs:/night.png");
	load_PNG(_100, "romfs:/100.png");
	load_PNG(_80, "romfs:/80.png");
	load_PNG(_60, "romfs:/60.png");
	load_PNG(_40, "romfs:/40.png");
	load_PNG(_20, "romfs:/20.png");
	load_PNG(_charge, "romfs:/charge.png");
	load_PNG(wifiIconFull, "romfs:/stat_sys_wifi_signal_4_fully.png");
	load_PNG(wifiIconNull, "romfs:/stat_sys_wifi_signal_null.png");
	load_PNG(highlight, "romfs:/highlight.png");
	
	if(setjmp(exitJmp)) 
	{
		cleanUp();
		return 0;
	}

	home(); // Show Home Menu, until the user presses START

	// Free textures before exiting
	sf2d_free_texture(background);
	sf2d_free_texture(cursor);
	sf2d_free_texture(quickSettings);
	sf2d_free_texture(navbar);
	sf2d_free_texture(backicon);
	sf2d_free_texture(homeicon);
	sf2d_free_texture(multicon);
	sf2d_free_texture(dayWidget);
	sf2d_free_texture(nightWidget);
	sf2d_free_texture(_100);
	sf2d_free_texture(_80);
	sf2d_free_texture(_60);
	sf2d_free_texture(_40);
	sf2d_free_texture(_20);
	sf2d_free_texture(_charge);
	sf2d_free_texture(wifiIconFull);
	sf2d_free_texture(wifiIconNull);
	sf2d_free_texture(highlight);

	sftd_free_font(robotoS10);
	sftd_free_font(robotoS12);
	sftd_free_font(robotoS18);
	sftd_free_font(robotoS30);
	cleanUp();
	
	return 0;
}

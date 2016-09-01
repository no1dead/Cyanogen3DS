#include "appDrawer.h"
#include "boot.h"
#include "homeMenu.h"
#include "lockScreen.h"
#include "main.h"
#include "settingsMenu.h"
#include "sound.h"
#include "utils.h"

void cleanUp() 
{
	sftd_fini();
	sf2d_fini();
	hidExit();
	sdmcExit();
	fsExit();
	amExit();
	httpcExit();
	ptmuExit();
    acExit();
    cfguExit();
	aptExit();
	srvExit();
}

int main(int argc, char **argv)
{
	srvInit();
	aptInit();
    cfguInit();
    acInit();
    ptmuInit();
	httpcInit(0);
	amInit();
	AM_InitializeExternalTitleDatabase(false);
	fsInit();
	sdmcInit();
	hidInit();
	
	// Font loading
	sf2d_init();
	sftd_init();
	
	sf2d_set_clear_color(RGBA8(0, 0, 0, 255));
	sf2d_set_vblank_wait(0);

	if ((getModel() == 2) || (getModel() == 4))
		osSetSpeedupEnable(true); //Enable N3DS speedup
	
	installRequiredFiles(); //create necessary dirs
	
	strcpy(backgroundPath, setFileDefaultsChar("/3ds/Cyanogen3DS/system/settings/background.bin", "/3ds/Cyanogen3DS/system/framework/framework-res/res/ventana.png", backgroundPath));
	
	hrTime = setFileDefaultsInt("/3ds/Cyanogen3DS/system/app/clock/timeSet.bin", 0, hrTime);
	DARK = setFileDefaultsInt("/3ds/Cyanogen3DS/system/settings/darkTheme.bin", 0, DARK);
	experimentalF = setFileDefaultsInt("/3ds/Cyanogen3DS/system/settings/experimentalFeatures.bin", 0, experimentalF);
	screenDisplay = setFileDefaultsInt("/3ds/Cyanogen3DS/system/settings/switchDisplay.bin", 0, screenDisplay);

	robotoS10 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);
	robotoS12 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);
	robotoS18 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);
	robotoS30 = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size);
	
	themesLoad();
	iconPackLoad();
	
	installFontColorData();

	// Load textures
	load_PNG(background, backgroundPath);
	load_PNG(cursor, cursorPath);
	load_PNG(quickSettings, quickSettingsBgPath);
	load_PNG(navbar, navbarPath);
	load_PNG(navbarHighlight, navbarHighlightPath);
	load_PNG(dayWidget, "/3ds/Cyanogen3DS/system/widget/day.png");
	load_PNG(nightWidget, "/3ds/Cyanogen3DS/system/widget/night.png");
	load_PNG(_100, "/3ds/Cyanogen3DS/system/home/icons/100.png");
	load_PNG(_80, "/3ds/Cyanogen3DS/system/home/icons/80.png");
	load_PNG(_60, "/3ds/Cyanogen3DS/system/home/icons/60.png");
	load_PNG(_40, "/3ds/Cyanogen3DS/system/home/icons/40.png");
	load_PNG(_20, "/3ds/Cyanogen3DS/system/home/icons/20.png");
	load_PNG(_charge, "/3ds/Cyanogen3DS/system/home/icons/charge.png");
	load_PNG(wifiIcon3, "/3ds/Cyanogen3DS/system/home/icons/stat_sys_wifi_signal_3.png");
	load_PNG(wifiIcon2, "/3ds/Cyanogen3DS/system/home/icons/stat_sys_wifi_signal_2.png");
	load_PNG(wifiIcon1, "/3ds/Cyanogen3DS/system/home/icons/stat_sys_wifi_signal_1.png");
	load_PNG(wifiIcon0, "/3ds/Cyanogen3DS/system/home/icons/stat_sys_wifi_signal_0.png");
	load_PNG(wifiIconNull, "/3ds/Cyanogen3DS/system/home/icons/stat_sys_wifi_signal_null.png");
	load_PNG(ic_allapps, allappsPath);
	load_PNG(ic_allapps_pressed, allapps_pressedPath);
	load_PNG(ic_launcher_browser, browserPath);
	load_PNG(ic_launcher_messenger, messagesPath);
	load_PNG(ic_launcher_apollo, apolloPath);
	load_PNG(ic_launcher_settings, settingsPath);
	load_PNG(welcome, "/3ds/Cyanogen3DS/system/home/icons/welcome.png");
	
	setBilinearFilter(1, background);
	setBilinearFilter(1, cursor);
	setBilinearFilter(1, quickSettings);
	setBilinearFilter(1, navbar);
	setBilinearFilter(1, navbarHighlight);
	setBilinearFilter(1, dayWidget);
	setBilinearFilter(1, nightWidget);
	setBilinearFilter(1, _100);
	setBilinearFilter(1, _80);
	setBilinearFilter(1, _60);
	setBilinearFilter(1, _40);
	setBilinearFilter(1, _20);
	setBilinearFilter(1, _charge);
	setBilinearFilter(1, wifiIcon3);
	setBilinearFilter(1, wifiIcon2);
	setBilinearFilter(1, wifiIcon1);
	setBilinearFilter(1, wifiIcon0);
	setBilinearFilter(1, wifiIconNull);
	setBilinearFilter(1, ic_launcher_browser);
	setBilinearFilter(1, ic_launcher_messenger);
	setBilinearFilter(1, ic_launcher_apollo);
	setBilinearFilter(1, ic_launcher_settings);
	
	if(setjmp(exitJmp)) 
	{
		cleanUp();
		return 0;
	}

	bootAnimation();

	// Free textures before exiting
	sf2d_free_texture(background);
	sf2d_free_texture(cursor);
	sf2d_free_texture(quickSettings);
	sf2d_free_texture(navbar);
	sf2d_free_texture(navbarHighlight);
	sf2d_free_texture(dayWidget);
	sf2d_free_texture(nightWidget);
	sf2d_free_texture(_100);
	sf2d_free_texture(_80);
	sf2d_free_texture(_60);
	sf2d_free_texture(_40);
	sf2d_free_texture(_20);
	sf2d_free_texture(_charge);
	sf2d_free_texture(wifiIcon3);
	sf2d_free_texture(wifiIcon2);
	sf2d_free_texture(wifiIcon1);
	sf2d_free_texture(wifiIcon0);
	sf2d_free_texture(wifiIconNull);
	sf2d_free_texture(highlight);

	sftd_free_font(robotoS10);
	sftd_free_font(robotoS12);
	sftd_free_font(robotoS18);
	sftd_free_font(robotoS30);
	cleanUp();
	
	return 0;
}

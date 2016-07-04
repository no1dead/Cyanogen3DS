# Cyanogen3DS [![Build Status](https://travis-ci.org/joel16/Cyanogen3DS.svg?branch=master)](https://travis-ci.org/joel16/Cyanogen3DS) [![Github latest downloads](https://img.shields.io/github/downloads/joel16/Cyanogen3DS/total.svg)](https://github.com/joel16/Cyanogen3DS/releases/latest)

This project is still heavily a work in progress. It is an alternative custom GUI menu for Nintendo 3DS. This program is based off of my PSP project - CyanogenPSP.

What's working
=================

- Battery Status (Displays the battery percentage, by using icons) and Wifi Status icons
- Lockscreen
- Navbar functions, for returning home or back to the previous menu
- Power menu (Allows access to exit to XMB, and launch recovery)
- Screenshots (Use R button to take screenshot)
- Security settings - Pin/Password lock and Swipe as default.
- Cyanogen3DS Dark Theme mode (Settings->Developer Options->Toggle Dark theme)
- Cyanogen3DS Experimental mode (Settings->Developer Options->Toggle Experimental features)
- Digital time and day/night widget
- Displays SD storage and CTR NAND storage statuses
- N3DS performance boost 

What's yet to work/Somewhat working
=================
- File manager - Delete files and folders, open text files, view pictures and play music files, rename files/folders and create new folders.
- OTA updates - (Settings->About->Cyanogen3DS Updates)
- Quick settings (Drop down menu)
- Icon pack manager (Settings->Display->Themes->Icon Packs)
- Multi language support (Settings->Display->Language) Available languages can be found here: https://www.transifex.com/cyanogenpsp/cyanogenpsp/
- Switch Display (Use bottom screen mostly rather than the top)
- Sounds 

What's not working
=================
- Everything else that isn't on the working list.

Developing Instructions
=================

Please check the [Wiki](https://github.com/joel16/Cyanogen3DS/wiki) for instructions on setting up, and beginning to develop.

###### A few notes:

If you use the 3dslink utility to launch Cyanogen3DS it gets stuck while launching with a blue bottom screen and debug text in the top. Try escaping this using the L+R+Down+B combo, hopefully it works.

Using START to exit doesn't quite work just yet, you need to escape with the same combo as above.

In the odd chance you use a CIA build (not official yet) then you WILL have issues (both mental issues and 3DS-related issues). Don't say you weren't warned.

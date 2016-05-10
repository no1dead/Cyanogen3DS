#pragma once

#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>

#include <unistd.h>
#include <setjmp.h>

#define NOT_FOUND_SIZE 32

#define load_PNG(texture, fname) { \
	if(access(fname, R_OK ) == -1 ) {\
		texture = sf2d_create_texture(NOT_FOUND_SIZE, NOT_FOUND_SIZE, TEXFMT_RGBA8, SF2D_PLACE_RAM); \
	} \
	else \
		texture = sfil_load_PNG_file(fname, SF2D_PLACE_RAM); \
	sf2d_texture_tile32(texture); \
}
/* Sometime in the future, I'll fill the file-not-found texture with grey or something
   Definitely not now */

jmp_buf exitJmp;   

void cleanUp();
int main(int argc, char **argv);

#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>

#define load_PNG(texture, fname, mode) {texture = sfil_load_PNG_file(fname, mode); sf2d_texture_tile32(texture);}

int main(int argc, char **argv);
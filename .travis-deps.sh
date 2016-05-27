#!/bin/sh
set -e
set -x

# Build and install devkitARM + ctrulib
wget http://sourceforge.net/projects/devkitpro/files/Automated%20Installer/devkitARMupdate.pl
git clone https://github.com/smealum/ctrulib.git
perl devkitARMupdate.pl

# Get latest ctrulib and overwrite bundled one
cd ctrulib/libctru && make ; cd -
cp -rf ctrulib/libctru/ ${DEVKITPRO}

# Get picasso
mv tools/picasso.exe ${PICASSO}

# Build and install portlibs
mkdir ${DEVKITPRO}/portlibs && mkdir ${PORTLIBS}
git clone https://github.com/devkitPro/3ds_portlibs.git
cd 3ds_portlibs

wget http://download.savannah.gnu.org/releases/freetype/freetype-2.5.4.tar.bz2
wget http://sourceforge.net/projects/libjpeg-turbo/files/1.3.1/libjpeg-turbo-1.3.1.tar.gz
wget http://prdownloads.sourceforge.net/libpng/libpng-1.6.15.tar.xz
wget http://prdownloads.sourceforge.net/libpng/zlib-1.2.8.tar.gz

make zlib
make install-zlib
make freetype
make libpng
make libjpeg-turbo
make install

cd -
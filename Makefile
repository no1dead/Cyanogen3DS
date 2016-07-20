#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#
# NO_SMDH: if set to anything, no SMDH file is generated.
# APP_TITLE is the name of the app stored in the SMDH file (Optional)
# APP_DESCRIPTION is the description of the app stored in the SMDH file (Optional)
# APP_AUTHOR is the author of the app stored in the SMDH file (Optional)
# ICON is the filename of the icon (.png), relative to the project folder.
#   If not set, it attempts to use one of the following (in this order):
#     - <Project name>.png
#     - icon.png
#     - <libctru folder>/default_icon.png
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# Resource Setup
#---------------------------------------------------------------------------------

TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
RESOURCES   :=	resources
SOURCES		:=	source
DATA		:=	data
INCLUDES	:=	source source/libs/sf2dlib/include source/libs/sftdlib/include source/libs/sfillib/include

APP_TITLE	:= Cyanogen3DS
APP_DESCRIPTION	:= An alternative Custom GUI Menu for 3DS.
APP_AUTHOR	:= Joel16

ICON := $(RESOURCES)/icon.png
BANNER := $(RESOURCES)/banner.png
JINGLE := $(RESOURCES)/banner.wav

# CIA
APP_PRODUCT_CODE := C3DS-GUI
APP_UNIQUE_ID := 0x16001
APP_SYSTEM_MODE := 64MB
APP_SYSTEM_MODE_EXT := Legacy

VERSION := '"Alpha-2.0"'

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

ARCH	:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard

CFLAGS	:=	-g -Wall -O2 -mword-relocations -Werror -DVERSION=$(VERSION)\
			-fomit-frame-pointer -ffast-math \
			$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM11 -D_3DS

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS	:= -lsfil -lpng -ljpeg -lz -lsf2d -lctru -lm -lsftd -lfreetype

OS := $(shell uname)

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------

LIBDIRS	:= $(CTRULIB) $(PORTLIBS) $(CURDIR)/source/libs/libsf2d $(CURDIR)/source/libs/libsfil $(CURDIR)/source/libs/libsftd

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------

ifneq ($(BUILD),$(notdir $(CURDIR)))

#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------

ifeq ($(strip $(CPPFILES)),)

#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------

else

#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------

endif

#---------------------------------------------------------------------------------

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

ifeq ($(strip $(ICON)),)
	icons := $(wildcard *.png)
	ifneq (,$(findstring $(TARGET).png,$(icons)))
		export APP_ICON := $(TOPDIR)/$(TARGET).png
	else
		ifneq (,$(findstring icon.png,$(icons)))
			export APP_ICON := $(TOPDIR)/icon.png
		endif
	endif
else
	export APP_ICON := $(TOPDIR)/$(ICON)
endif

ifeq ($(strip $(NO_SMDH)),)
	export _3DSXFLAGS += --smdh=$(CURDIR)/$(TARGET).smdh
endif

#---------------------------------------------------------------------------------
# 3DS CIA
#---------------------------------------------------------------------------------
export BUILD_ARGS := \
-DAPP_TITLE=$(APP_TITLE) \
-DAPP_PRODUCT_CODE=$(APP_PRODUCT_CODE) \
-DAPP_UNIQUE_ID=$(APP_UNIQUE_ID) \
-DAPP_SYSTEM_MODE=$(APP_SYSTEM_MODE) \
-DAPP_SYSTEM_MODE_EXT=$(APP_SYSTEM_MODE_EXT) \
-elf $(OUTPUT).elf -rsf "$(TOPDIR)/resources/cia.rsf" \
-icon $(TOPDIR)/icon.bin \
-banner $(TOPDIR)/banner.bin -exefslogo -target t

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------

all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

build-sf2dlib:
	@make -C source/libs/libsf2d build

build-sftdlib:
	@make -C source/libs/libsftd build

build-sfillib:
	@make -C source/libs/libsfil build

build-all:
	@echo $(BUILD_ARGS)
	@echo Building sf2dlib...
	@make build-sf2dlib
	@echo Building sftdlib...
	@make build-sftdlib
	@echo Building sfillib...
	@make build-sfillib
	@echo Building Cyanogen3DS...
	@make build

#---------------------------------------------------------------------------------
clean:
	@rm -fr $(BUILD) $(TARGET).3dsx $(OUTPUT).smdh $(OUTPUT).elf $(OUTPUT).3ds $(TARGET).cia icon.bin banner.bin

clean-sf2dlib:
	@make -C source/libs/libsf2d clean

clean-sftdlib:
	@make -C source/libs/libsftd clean

clean-sfillib:
	@make -C source/libs/libsfil clean

clean-all:
	@echo Cleaning sf2dlib...
	@make clean-sf2dlib
	@echo Cleaning sftdlib...
	@make clean-sftdlib
	@echo Cleaning sfillib...
	@make clean-sfillib
	@echo Cleaning Cyanogen3DS...
	@make clean
	
#---------------------------------------------------------------------------------

banner:
	@$(TOPDIR)/tools/bannertool

#---------------------------------------------------------------------------------
	
cia: clean all
	@arm-none-eabi-strip $(TARGET).elf
	@makerom -f cia -o $(TARGET).cia -elf $(TARGET).elf -rsf $(RESOURCE)/cia.rsf -icon $(RESOURCES)/icon.png -banner $(RESOURCES)/banner.png -exefslogo -target t
	
#---------------------------------------------------------------------------------

$(TARGET)-strip.elf: $(BUILD)
	@$(STRIP) --strip-all $(TARGET).elf -o $(TARGET)-strip.elf

#---------------------------------------------------------------------------------

send: $(BUILD)
	@3dslink $(TARGET).3dsx

#---------------------------------------------------------------------------------

run: $(BUILD)
	@citra $(TARGET).3dsx

#---------------------------------------------------------------------------------

else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

ifeq ($(strip $(NO_SMDH)),)
$(OUTPUT).3dsx	:	$(OUTPUT).smdh icon.bin banner.bin $(OUTPUT).elf $(OUTPUT).3ds $(OUTPUT).cia
else
$(OUTPUT).3dsx	:	icon.bin banner.bin $(OUTPUT).elf $(OUTPUT).3ds $(OUTPUT).cia
endif

#---------------------------------------------------------------------------------
icon.bin	:	
#---------------------------------------------------------------------------------

ifeq ($(OS), Linux)
	@$(TOPDIR)/tools/linux/bannertool makesmdh -s $(APP_TITLE) -l $(APP_TITLE) -p $(APP_AUTHOR) -i $(TOPDIR)/$(ICON) -o $(TOPDIR)/icon.bin -f visible allow3d
else ifeq ($(OS), Darwin)
	@$(TOPDIR)/tools/osx/bannertool makesmdh -s $(APP_TITLE) -l $(APP_TITLE) -p $(APP_AUTHOR) -i $(TOPDIR)/$(ICON) -o $(TOPDIR)/icon.bin -f visible allow3d
else
	@$(TOPDIR)/tools/windows/bannertool.exe makesmdh -s $(APP_TITLE) -l $(APP_TITLE) -p $(APP_AUTHOR) -i $(TOPDIR)/$(ICON) -o $(TOPDIR)/icon.bin -f visible allow3d
endif

#---------------------------------------------------------------------------------
banner.bin	:	
#---------------------------------------------------------------------------------

ifeq ($(OS), Linux)
	@$(TOPDIR)/tools/linux/bannertool makebanner -i $(TOPDIR)/$(BANNER) -a $(TOPDIR)/$(JINGLE) -o $(TOPDIR)/banner.bin
else ifeq ($(OS), Darwin)
	@$(TOPDIR)/tools/osx/bannertool makebanner -i $(TOPDIR)/$(BANNER) -a $(TOPDIR)/$(JINGLE) -o $(TOPDIR)/banner.bin
else
	@$(TOPDIR)/tools/windows/bannertool.exe makebanner -i $(TOPDIR)/$(BANNER) -a $(TOPDIR)/$(JINGLE) -o $(TOPDIR)/banner.bin
endif

#---------------------------------------------------------------------------------
$(OUTPUT).elf	:	$(OFILES)
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
$(OUTPUT).3ds	:	$(OUTPUT).elf icon.bin banner.bin
#---------------------------------------------------------------------------------

ifeq ($(OS), Linux)
	@$(TOPDIR)/tools/linux/makerom -f cci -o $(OUTPUT).3ds $(BUILD_ARGS)
else ifeq ($(OS), Darwin)
	@$(TOPDIR)/tools/osx/makerom -f cci -o $(OUTPUT).3ds $(BUILD_ARGS)
else
	@$(TOPDIR)/tools/windows/makerom.exe -f cci -o $(OUTPUT).3ds $(BUILD_ARGS)
endif
	@echo 3DS packaged ...

#---------------------------------------------------------------------------------
$(OUTPUT).cia	:	$(OUTPUT).elf icon.bin banner.bin
#---------------------------------------------------------------------------------

ifeq ($(OS), Linux)
	@$(TOPDIR)/tools/linux/makerom -f cia -o $(OUTPUT).cia $(BUILD_ARGS)
else ifeq ($(OS), Darwin)
	@$(TOPDIR)/tools/osx/makerom -f cia -o $(OUTPUT).cia $(BUILD_ARGS)
else
	@$(TOPDIR)/tools/windows/makerom.exe -f cia -o $(OUTPUT).cia $(BUILD_ARGS)
endif
	@echo CIA packaged ...

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------

%.bin.o	:	%.bin

#---------------------------------------------------------------------------------

	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.ttf.o	:	%.ttf
#---------------------------------------------------------------------------------

	@echo $(notdir $<)
	@$(bin2o)

# WARNING: This is not the right way to do this! TODO: Do it right!
#---------------------------------------------------------------------------------
%.vsh.o	:	%.vsh
#---------------------------------------------------------------------------------

	@echo $(notdir $<)
	@picasso -o $(notdir $<).shbin $<
	@bin2s $(notdir $<).shbin | $(PREFIX)as -o $@
	@echo "extern const u8" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"_end[];" > `(echo $(notdir $<).shbin | tr . _)`.h
	@echo "extern const u8" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" >> `(echo $(notdir $<).shbin | tr . _)`.h
	@echo "extern const u32" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(notdir $<).shbin | tr . _)`.h

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
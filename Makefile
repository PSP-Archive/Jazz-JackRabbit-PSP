TARGET = jazz
PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
SDL_CONFIG = $(PSPBIN)/sdl-config

PSP_EBOOT_ICON = ICON0.PNG
#PSP_EBOOT_PIC1 = PIC1.PNG




OBJS = bonus.o \
events.o \
font.o \
level.o \
main.o \
menu.o \
planet.o \
scene.o \
sound.o

INCDIR = 
CFLAGS = -O2 -g  -G0 -Wall $(shell $(SDL_CONFIG) --cflags)  -DFULLSCREEN_ONLY=1
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lstdc++  -lSDL_mixer  -lvorbisidec -lSDL_image -lpng -lz -ljpeg \
        -lSDL_gfx -lm $(shell $(SDL_CONFIG) --libs)  -lpsppower

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = jazz

include $(PSPSDK)/lib/build.mak

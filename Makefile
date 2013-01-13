Sources=input/Keyboard.cpp InputState.cpp Renderer.cpp Game.cpp
Executable=Tiles

UNAME=$(shell uname)

CFlags=-c -Wall -g -Iinc

ObjectDir=build/
SourceDir=lib/
BuildDir=bin/

RM=rm

# OSX Specific compile flags
ifeq ($(UNAME), Darwin)
CC=g++
LDFlags=$(shell sdl2-config --cflags --static-libs) \
				-I/usr/local/Cellar/freeimage/3.15.4/include  \
				-L/usr/local/Cellar/freeimage/3.15.4/lib \
				-lfreeimage
endif

# Windows compile flags
ifeq ($(OS),Windows_NT)
CC=mingw32-g++.exe

# Include headers in vendor/windows/include
CFlags+=-Ivendor/windows/include

LDFlags=-Ivendor/windows/include \
        -Lvendor/windows/bin \
        -Lvendor/windows/lib \
        -lFreeImage \
        -lglew32 \
        -lmingw32 -lSDLmain -lSDL
endif

#!!!!!DO NOT EDIT ANYTHING UNDER THIS LINE!!!!!
Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BuildDir),$(Executable))

all: $(CSources) $(CExecutable)

$(CExecutable): prepare $(CObjects)
	$(CC) $(LDFlags) $(CObjects) main.cpp -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	mkdir -p `dirname $@`
	$(CC) $(CFlags) $< -o $@

prepare:
	mkdir -p $(BuildDir)

test: all
	./$(BuildDir)$(Executable)

clean:
	rm -rf $(BuildDir)
	rm -rf $(ObjectDir)
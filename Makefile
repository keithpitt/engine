Sources=input/Keyboard.cpp InputState.cpp Renderer.cpp Game.cpp
Executable=Tiles

CFlags=-c -Wall -g -Iinc
LDFlags=$(shell sdl-config --cflags --static-libs) \
				-I/usr/local/Cellar/freeimage/3.15.4/include  \
				-L/usr/local/Cellar/freeimage/3.15.4/lib \
				-lfreeimage
ObjectDir=build/
SourceDir=lib/
BuildDir=bin/

CC=g++
RM=rm

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

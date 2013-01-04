Sources=InputHandler.cpp Renderer.cpp Game.cpp
Executable=Tiles

CFlags=-c -Wall -g -Iinc
LDFlags=$(shell sdl-config --cflags --static-libs)
ObjectDir=build/
SourceDir=src/
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
	$(CC) $(CFlags) $< -o $@

prepare:
	mkdir -p $(ObjectDir)
	mkdir -p $(BuildDir)

test: all
	./$(BuildDir)$(Executable)

clean:
	$(RM) $(CObjects)

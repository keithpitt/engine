CC=g++
NAME=Tiles
DIR=build
CFLAGS=`sdl-config --cflags --static-libs`
all:
	mkdir -p $(DIR)
	$(CC) src/settings.cpp src/shared.cpp main.cpp -o $(DIR)/$(NAME) $(CFLAGS)
test: all
	./$(DIR)/$(NAME)
clean:
	rm -rf $(DIR)
	rm -rf $(NAME).app
prepare:
	mkdir -p $(DIR)
bundle: all
	rm -rf $(NAME).app
	mkdir -p $(NAME)/Contents/MacOS
	mkdir -p $(NAME)/Contents/Resources
	cp $(DIR)/$(NAME) $(NAME)/Contents/MacOS/$(NAME)
	touch $(NAME)/Contents/Info.plist
	mv $(NAME) $(NAME).app
dist: bundle
	cp -R $(NAME).app ~/Dropbox/Games/

CC=llvm-g++-4.2
NAME=Tiles
DIR=build
test: all
	./$(DIR)/$(NAME)
clean:
	rm -rf $(NAME).app
	rm -rf $(NAME).zip
all:
	mkdir -p $(DIR)
	$(CC) main.cpp -o $(DIR)/$(NAME) -lsfml-window -framework OpenGL -framework Cocoa
bundle: all
	rm -rf $(NAME).app
	mkdir -p $(NAME)/Contents/MacOS
	mkdir -p $(NAME)/Contents/Resources
	cp $(DIR)/$(NAME) $(NAME)/Contents/MacOS/$(NAME)
	touch $(NAME)/Contents/Info.plist
	mv $(NAME) $(NAME).app
dist: bundle
	cp -R $(NAME).app ~/Dropbox/Games/

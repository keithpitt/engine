NAME=Tiles
DIR=build
clean:
	rm -rf $(NAME).app
	rm -rf $(NAME).zip
test: all
	./$(DIR)/$(NAME)
all:
	mkdir -p $(DIR)
	g++ main.cpp -o $(DIR)/$(NAME) -lsfml-window -framework OpenGL
bundle: all
	rm -rf $(NAME).app
	mkdir -p $(NAME)/Contents/MacOS
	mkdir -p $(NAME)/Contents/Resources
	cp $(DIR)/$(NAME) $(NAME)/Contents/MacOS/$(NAME)
	touch $(NAME)/Contents/Info.plist
	mv $(NAME) $(NAME).app
dist: bundle
	cp -R $(NAME).app ~/Dropbox/Games/

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main() {
  std::cout << "hello";

  // Create the window
  sf::Window window(sf::VideoMode(1280, 720), "Tiles");
  // window.setVerticalSyncEnabled(true);

  // The main loop
  bool running = true;
  while(running) {
    // Handle events
    sf::Event event;

    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        running = false;
      } else if(event.type == sf::Event::Resized) {
        glViewport(0, 0, event.size.width, event.size.height);
      }
    }

    // Clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // End the current window frame (actually swaps the front and back buffers)
    window.display();
  }

  return 0;
}

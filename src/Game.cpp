#include "Game.h"

#include <SDL/SDL.h>

#include "Settings.h"
#include "InputHandler.h"
#include "Renderer.h"

Game::Game() {
  renderer = new Renderer("Hey!", RESOLUTION_WIDTH, RESOLUTION_HEIGHT, MAX_FPS);
  inputHandler = new InputHandler();
}

int Game::Run() {
  running = true;

  while(running) {
    renderer->BeginDraw();
    inputHandler->Update();
    renderer->EndDraw();
  }

  return 0;
}

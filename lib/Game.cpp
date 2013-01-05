#include "Game.h"

#include "Settings.h"

#include "InputState.h"
#include "input/Keyboard.h"

#include "Renderer.h"

Game::Game() {
  renderer = new Renderer("Hey!", RESOLUTION_WIDTH, RESOLUTION_HEIGHT, MAX_FPS);
  inputState = new InputState();
}

int Game::Run() {
  running = true;

  while(running) {
    renderer->BeginDraw();
    inputState->Update();

    if(inputState->keyboard->IsKeyDown(KEYBOARD_ESC)) {
      running = false;
      break;
    }

    if(inputState->keyboard->IsMetaKeyDown() &&
        inputState->keyboard->IsKeyDown(KEYBOARD_q)) {
      running = false;
      break;
    }

    renderer->Update(inputState);
    renderer->EndDraw();
  }

  delete renderer;
  delete inputState;

  return 0;
}

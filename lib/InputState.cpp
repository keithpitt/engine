#include <SDL/SDL.h>

#include "InputState.h"
#include "Keyboard.h"
#include "Debug.h"

InputState::InputState() {
  keyboard = new Keyboard();
}

InputState::~InputState() {
  log("Cleaning up the input state.");
  delete keyboard;
}

void InputState::Update() {
  SDL_Event   event;

  while(SDL_PollEvent(&event)) {
    // Handle OS quit events
    if(event.type == SDL_QUIT) {
      // TODO: Find a nice way to deal with this one.
      //   running = false;
      break;
    }

    // Foward the SDL event onto the keyboard so it can update
    // its internal mapping of what keys are up and down.
    if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      keyboard->UpdateSDLEvent(event);
    }
  }
}

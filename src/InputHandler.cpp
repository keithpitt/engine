#include <SDL2/SDL.h>

#include "InputHandler.h"

void InputHandler::Update() {
  SDL_PumpEvents();

  // int numberOfKeyboards = SDL_GetNumKeyboards();
};

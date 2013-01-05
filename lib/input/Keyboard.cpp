#include <SDL2/SDL.h>

#include "Keyboard.h"
#include "../Debug.h"

const int KEYBOARD_ESC = SDLK_ESCAPE;
const int KEYBOARD_q = SDLK_q;

Keyboard::Keyboard() {
  // This line here is so very very wrong.
  this->keys.reserve(1073741907);
  this->altKey = false;
  this->metaKey = false;
}

void Keyboard::UpdateSDLEvent(SDL_Event event) {
  SDL_Keycode key   = event.key.keysym.sym;
  uint16_t modifier = event.key.keysym.mod;

  // debug("%s key state change", SDL_GetKeyName(key));

  // Handle key down events
  if(event.type == SDL_KEYDOWN) {
    this->SetKey(key, true);

    // meta key pressed
    if(event.key.keysym.mod & KMOD_LGUI)
      this->SetMetaKey(true);

    // alt pressed
    if(event.key.keysym.mod & KMOD_ALT)
      this->SetAltKey(true);
  }

  // Key up events
  if(event.type == SDL_KEYUP) {
    this->SetKey(key, false);

    // alt up
    if(modifier & KMOD_ALT) {
    }
  }
}

void Keyboard::SetMetaKey(bool down) {
  this->metaKey = down;
}

bool Keyboard::IsMetaKeyDown() {
  return this->metaKey;
}

void Keyboard::SetAltKey(bool down) {
  this->altKey = down;
}

bool Keyboard::IsAltKeyDown() {
  return this->altKey;
}

void Keyboard::SetKey(unsigned int key, bool down) {
  this->keys[key] = down;
}

bool Keyboard::IsKeyDown(unsigned int key) {
  return this->keys[key];
}

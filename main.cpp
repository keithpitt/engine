#include <SDL/SDL.h>

#include "src/shared.h"
#include "src/settings.h"

void loop() {
  bool running = true;

  uint32_t delay = 1000 / MAX_FPS;
  uint32_t offset;
  uint32_t start;

  while(running) {
    start = SDL_GetTicks();

    SDL_PumpEvents();

    int offset = SDL_GetTicks() - start;
    if(delay > offset)
      SDL_Delay(delay - offset);
  }
}

void init() {
  // Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  // Initialize the SDL surface
  SDL_Surface *surface = SDL_SetVideoMode(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 32, SDL_SWSURFACE|SDL_OPENGL);
  if (surface == NULL) {
    fprintf(stderr, "Error during SDL_SetVideoMode: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
}

int main(int argc, char** argv) {
  init();
  loop();

  // return Engine::Run();
  return 0;
}

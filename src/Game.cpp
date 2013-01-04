#include "Game.h"

#include <iostream>
#include <SDL/SDL.h>
#include "OpenGL.h"
#include "Settings.h"

Game::Game() {
  // Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  // Initialize the SDL surface
  SDL_Surface *surface = NULL;
  surface = SDL_SetVideoMode(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 32, SDL_SWSURFACE|SDL_OPENGL);

  if (surface == NULL) {
    fprintf(stderr, "Error during SDL_SetVideoMode: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0.0, -1.0, 1.0);
}

int Game::Run() {
  uint32_t delay = 1000 / MAX_FPS;
  uint32_t offset;
  uint32_t start;

  SDL_Event event;

  running = true;

  while(running) {
    start = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    while(SDL_PollEvent(&event)) {

      // Handle OS quit events
      if(event.type == SDL_QUIT) {
        running = false;
        break;
      }

      // Handle key down events
      if(event.type == SDL_KEYDOWN) {
        // debug("%s key pressed.", SDL_GetKeyName(key));
        SDLKey key      = event.key.keysym.sym;
        SDLMod modifier = event.key.keysym.mod;

        // Handling CMD+Q for OSX
        if((modifier & KMOD_META) && key == SDLK_q) {
          running = false;
          break;
        }

        // Handle ALT-F4
        if((modifier & KMOD_ALT) && key == SDLK_F4) {
          running = false;
          break;
        }
      }

      // debug("unhandled event %i", event.type);
    }

    SDL_GL_SwapBuffers();

    offset = SDL_GetTicks() - start;
    if(delay > offset)
      SDL_Delay(delay - offset);
  }

  return 0;
}

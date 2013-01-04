#include "Engine.h"

void Engine::setup() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Surface * screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE|SDL_OPENGL);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);
}

void Engine::loop() {
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

    int offset = SDL_GetTicks() - start;
    if((1000 / FPS) > offset)
      SDL_Delay((1000 / FPS) - offset);
  }
}

int Engine::run() {
  setup();
  loop();

  return 0;
}

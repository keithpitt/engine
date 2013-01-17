#include <SDL.h>
#include "OpenGL.h"

#include "InputState.h"
#include "Keyboard.h"
#include "Renderer.h"
#include "Debug.h"

// For more info about how we use SDL, see this:
// http://wiki.libsdl.org/moin.cgi/SDL_GL_CreateContext?highlight=%28SDL%5C_OPENGL%29

Renderer::Renderer(char *title, int width, int height, int fps) {
  this->title = title;
  this->width = width;
  this->height = height;
  this->fps = fps;

  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);

  // Create an SDL surface. Window mode MUST include SDL_OPENGL for use with OpenGL.
  surface = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  if (surface == NULL) {
    fprintf(stderr, "Error during SDL_SetVideoMode: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, width, 0, height, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);

  // Enable alpha-channel transparency on textures
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);

  start  = SDL_GetTicks();
  delay  = 1000 / fps;
  frames = 0;
}

Renderer::~Renderer() {
  log("Cleaning up window.");

  // TODO for SDL 1.2
  // SDL_GL_DeleteContext(glcontext);
  // SDL_DestroyWindow(window);
}

void Renderer::Update(InputState *inputState) {
  if(inputState->keyboard->IsKeyDown(SDLK_UP)) {
    log("Up pressed.");
  }
}

void Renderer::BeginDraw() {
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();

  ++frames;
}

void Renderer::EndDraw() {
  SDL_GL_SwapBuffers();

  offset = SDL_GetTicks() - start;
  float fps = ((float)frames / (float)offset) * 1000;

  debug("FPS: %f", fps);

  if(delay > offset)
    SDL_Delay(delay - offset);
}
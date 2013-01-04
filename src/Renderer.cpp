#include "Renderer.h"

#include <SDL/SDL.h>
#include "OpenGL.h"

Renderer::Renderer(int width, int height, int fps) {
  this->width = width;
  this->height = height;

  // Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  // Initialize the SDL surface
  SDL_Surface *surface = NULL;
  surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE|SDL_OPENGL);

  if (surface == NULL) {
    fprintf(stderr, "Error during SDL_SetVideoMode: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, width, height, 0.0, -1.0, 1.0);

  delay = 1000 / fps;
}

void Renderer::BeginDraw() {
  start = SDL_GetTicks();

  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void Renderer::EndDraw() {
  SDL_GL_SwapBuffers();

  offset = SDL_GetTicks() - start;
  if(delay > offset)
    SDL_Delay(delay - offset);
}

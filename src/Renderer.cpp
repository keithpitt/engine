#include <SDL2/SDL.h>
#include "OpenGL.h"

#include "Renderer.h"

// For more info about how we use SDL, see this:
// http://wiki.libsdl.org/moin.cgi/SDL_GL_CreateContext?highlight=%28SDL%5C_OPENGL%29

Renderer::Renderer(char *title, int width, int height, int fps) {
  this->title = title;
  this->width = width;
  this->height = height;
  this->fps = fps;

  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);

  // Create a window. Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
  window = SDL_CreateWindow(title,
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      width, height,
      SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

  // Create an OpenGL context associated with the window.
  glcontext = SDL_GL_CreateContext(window);
  if (glcontext == NULL) {
    fprintf(stderr, "Error during SDL_GL_CreateContext: %s\n", SDL_GetError());
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
  SDL_GL_SwapWindow(window);

  offset = SDL_GetTicks() - start;
  if(delay > offset)
    SDL_Delay(delay - offset);
}

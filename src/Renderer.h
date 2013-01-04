#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <stdint.h>

class SDL_Window;
typedef void *SDL_GLContext;

class Renderer {
  private:
    uint32_t delay;
    uint32_t offset;
    uint32_t start;

    SDL_Window *window;
    SDL_GLContext glcontext;

  public:
    char *title;
    int width;
    int height;
    int fps;

    Renderer(char *title, int width, int height, int fps);
    void BeginDraw();
    void EndDraw();
};

#endif

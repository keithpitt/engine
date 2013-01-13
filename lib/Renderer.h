#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <stdint.h>

class SDL_Surface;
class InputState;

class Renderer {
  private:
    uint32_t delay;
    uint32_t offset;
    uint32_t start;

    int frames;

    SDL_Surface* surface;

  public:
    char *title;
    int width;
    int height;
    int fps;

    Renderer(char *title, int width, int height, int fps);
    ~Renderer();

    void Update(InputState *inputState);
    void BeginDraw();
    void EndDraw();
};

#endif

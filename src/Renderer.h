#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <stdint.h>

class Renderer {
  uint32_t delay;
  uint32_t offset;
  uint32_t start;

  public:
    int width;
    int height;
    int fps;

    Renderer(int width, int height, int fps);
    void BeginDraw();
    void EndDraw();
};

#endif

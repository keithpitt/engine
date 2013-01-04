#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <SDL/SDL.h>

class InputHandler {
  private:
    SDL_Event event;

  public:
    void Update();
};

#endif

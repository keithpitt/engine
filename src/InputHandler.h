#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

typedef union SDL_Event;

class InputHandler {
  private:
    SDL_Event event;

  public:
    void Update();
};

#endif

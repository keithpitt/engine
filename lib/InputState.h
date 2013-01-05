#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <stdint.h>

class Keyboard;

class InputState {
  public:
    Keyboard* keyboard;

    InputState();
    ~InputState();

    void Update();
};

#endif

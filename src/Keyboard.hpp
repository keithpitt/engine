#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <SDL.h>
#include <vector>

extern const int KEYBOARD_ESC;

extern const int KEYBOARD_q;
extern const int KEYBOARD_w;
extern const int KEYBOARD_n;
extern const int KEYBOARD_r;

extern const int KEYBOARD_UP;
extern const int KEYBOARD_DOWN;
extern const int KEYBOARD_LEFT;
extern const int KEYBOARD_RIGHT;

class Keyboard {
  private:
    std::vector<bool> keys;
    bool metaKey;
    bool altKey;

  public:
    Keyboard();

    void UpdateSDLEvent(SDL_Event event);

    void SetKey(unsigned int key, bool down);
    bool IsKeyDown(unsigned int key);

    void SetMetaKey(bool down);
    bool IsMetaKeyDown();

    void SetAltKey(bool down);
    bool IsAltKeyDown();
};

#endif

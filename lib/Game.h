#ifndef _GAME_H_
#define _GAME_H_

class InputState;
class Renderer;

class Game {
  private:
    bool running;

    InputState* inputState;
    Renderer* renderer;

  public:
    Game();

    int Run();
};

#endif

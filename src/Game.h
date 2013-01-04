#ifndef _GAME_H_
#define _GAME_H_

class InputHandler;
class Renderer;

class Game {
  private:
    bool running;

    InputHandler* inputHandler;
    Renderer* renderer;

  public:
    Game();

    int Run();
};

#endif

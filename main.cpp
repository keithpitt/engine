#include <SDL/SDL.h>
#include "src/Game.h"

int main(int argc, char** argv) {
  Game *game = new Game();
  int returnValue = game->Run();
  delete game;

  return returnValue;
}

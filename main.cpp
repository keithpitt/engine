#include <SDL/SDL.h> // Need to include SDL here so it can hack around with SDL_Main etc.
#include "lib/Game.h"

int main(int argc, char** argv) {
  Game *game = new Game();
  int returnValue = game->Run();
  delete game;

  return returnValue;
}

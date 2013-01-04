#ifndef _ENGINE_H_
#define _ENGINE_H_
#include "OpenGL.h"

class Engine {
  private:
    bool running;
    void setup();
    void loop();

  public:
    virtual int Run() {
      Engine engine;

      return engine.run();
    };

    int run();
};

#endif

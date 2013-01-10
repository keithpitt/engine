#include "Game.h"

#include "Settings.h"

#include "InputState.h"
#include "input/Keyboard.h"

#include "Renderer.h"

#include <FreeImage.h>

#include "Debug.h"
#include "OpenGL.h"

FIBITMAP* loadImage(const char* path) {
  // This will return the type of image. We could just manually pass in
  // FIF_PNG to FreeImage_Load, but that'd be no fun :D
  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path, 0);
  FIBITMAP *image = FreeImage_Load(format, path);

  if(image) {
    int w = FreeImage_GetWidth(image);
    int h = FreeImage_GetHeight(image);

    debug("Loading image %s %ix%i", path, w, h);

    return image;
  } else {
    exit(1);
  }
};

void freeImage(FIBITMAP *image) {
  FreeImage_Unload(image);
}

GLuint createTexture(FIBITMAP *image) {
  // To start things off, we first need a texture name.
  // This is essentially a number that OpenGL uses to index all the different textures.
  GLuint texture;

  // Generate 1 texture name, and assign it to the texture variable
  glGenTextures(1, &texture);

  // This sets the current texture so we can start playing with. We also need to tell it
  // what sort of texture it is. In most cases, its a 2d texure.
  // Note: A 2d texture has height and width. A 1d texture is just a row of pixels.
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  int w = FreeImage_GetWidth(image);
  int h = FreeImage_GetHeight(image);

  // Pointer to the bits data
  BYTE* bits(0);
  bits = FreeImage_GetBits(image);

  GLubyte* textura = new GLubyte[4*w*h];
  char* pixeles = (char*)FreeImage_GetBits(image);
  //FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
 
  for(int j= 0; j<w*h; j++){
    textura[j*4+0]= pixeles[j*4+2];
    textura[j*4+1]= pixeles[j*4+1];
    textura[j*4+2]= pixeles[j*4+0];
    textura[j*4+3]= pixeles[j*4+3];
    //cout<<j<<": "<<textura[j*4+0]<<"**"<<textura[j*4+1]<<"**"<<textura[j*4+2]<<"**"<<textura[j*4+3]<<endl;
  }


  // debug("Creating texture %ix%i (%i)", w, h, bits);

  // build our texture mipmaps
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)textura);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


  return texture;

};

void freeImageErrorHandler(FREE_IMAGE_FORMAT format, const char* message) {
  debug("Failed to load image: %s", message);
};

Game::Game() {
  renderer = new Renderer("Hey!", RESOLUTION_WIDTH, RESOLUTION_HEIGHT, MAX_FPS);
  inputState = new InputState();

  FreeImage_SetOutputMessage(freeImageErrorHandler);

}

int Game::Run() {
  running = true;

  FIBITMAP *image = loadImage("assets/sprite.png");
  GLuint testTexture = createTexture(image);
  freeImage(image);

  int w = 256.0;
  int h = 192.0;

  int x = 100;
  int y = 100;
  int size = 4;

  while(running) {
    renderer->BeginDraw();
    inputState->Update();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, testTexture);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(x, y);
    glTexCoord2d(1.0,0.0); glVertex2d(x + w, y);
    glTexCoord2d(1.0,1.0); glVertex2d(x + w, y + h);
    glTexCoord2d(0.0,1.0); glVertex2d(x, y + h);
    glEnd();

    if(inputState->keyboard->IsKeyDown(KEYBOARD_q)) {
      w = w - size;
      h = h - size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_w)) {
      w = w + size;
      h = h + size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_UP)) {
      y += size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_DOWN)) {
      y -= size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_LEFT)) {
      x -= size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_RIGHT)) {
      x += size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_ESC)) {
      running = false;
      break;
    }

    if(inputState->keyboard->IsMetaKeyDown() &&
        inputState->keyboard->IsKeyDown(KEYBOARD_q)) {
      running = false;
      break;
    }

    renderer->Update(inputState);
    renderer->EndDraw();
  }

  delete renderer;
  delete inputState;

  return 0;
}

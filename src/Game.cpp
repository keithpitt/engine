#include "Game.hpp"

#include "Settings.hpp"

#include "InputState.hpp"
#include "Keyboard.hpp"

#include "Renderer.hpp"

#include <FreeImage.h>

#include "Debug.hpp"
#include "OpenGL.hpp"

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


  // debug("Creating texture %ix%i (%i)", w, h, bits);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);


  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // The magnification function ("linear" produces better results)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // If the u,v coordinates overflow the range 0,1 the image is repeated
  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_STRETCH); 
  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // build our texture mipmaps
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_BGRA, GL_UNSIGNED_BYTE, bits);

  return texture;

};

void freeImageErrorHandler(FREE_IMAGE_FORMAT format, const char* message) {
  debug("Failed to load image: %s", message);
};

Game::Game() {
  char* title = (char *)"Hey!";
  renderer = new Renderer(title, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, MAX_FPS);
  inputState = new InputState();

  FreeImage_SetOutputMessage(freeImageErrorHandler);

}

int Game::Run() {
  running = true;

  FIBITMAP *image = loadImage("../assets/sprite.png");
  GLuint testTexture = createTexture(image);
  freeImage(image);


  int x = 100;
  int y = 100;
  int w = 256;
  int h = 256;
  int r = 0;
  int size = 4;

  float spriteUp = 0;
  float spriteLeft = 3;

  bool changed = false;

  while(running) {
    renderer->BeginDraw();
    inputState->Update();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, testTexture);

    glLoadIdentity();
    glTranslatef(x, y, 0);

    int centreX = w / 2;
    int centreY = h / 2;

    glTranslatef(centreX, centreY, 0);
    glRotatef(r, 0, 0, 1);
    glTranslatef(-centreX, -centreY, 0);

    float textureHeight = 256.0;
    float textureWidth = 256.0;

    float spriteWidth = 64;
    float spriteHeight = 64;
    float spriteX = spriteLeft * spriteWidth;
    float spriteY = spriteUp * spriteHeight;

    glBegin(GL_QUADS);

    //glTexCoord2d(spritex/(double)texturew,spritey/(double)textureh);
    glTexCoord2f(spriteX / textureWidth,
                 spriteY / textureHeight);
    glVertex2f(0, 0);

    //glTexCoord2d((spritex+w)/(double)texturew,spritey/(double)textureh);
    glTexCoord2f((spriteX + spriteWidth) / textureWidth,
                  spriteY / textureHeight);
    glVertex2f(w, 0);

    //glTexCoord2d((spritex+w)/(double)texturew,(spritey+h)/(double)textureh);
    glTexCoord2f((spriteX + spriteWidth) / textureWidth,
                 (spriteY + spriteHeight) / textureHeight);
    glVertex2f(w, h);

    //glTexCoord2d(spritex/(double)texturew,(spritey+h)/(double)textureh);
    glTexCoord2f(spriteX / textureWidth,
                (spriteY + spriteHeight) / textureHeight);
    glVertex2f(0, h);

    glEnd();

    if(inputState->keyboard->IsKeyDown(KEYBOARD_n)) {
      if(!changed) {
        spriteLeft += 1;

        if(spriteLeft > 3) {
          spriteLeft = 0;
          spriteUp += 1;

          if(spriteUp > 3) {
            spriteUp = 0;
          }
        }
        changed = true;
      }
    } else {
      changed = false;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_q)) {
      w = w - size;
      h = h - size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_w)) {
      w = w + size;
      h = h + size;
    }

    if(inputState->keyboard->IsKeyDown(KEYBOARD_r)) {
      r = r + 10;
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

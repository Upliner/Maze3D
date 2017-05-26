#ifndef OPENGL_H
#define OPENGL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "defines.h"

struct buffer {
  byte *buf;
  buffer(int size) {
    buf = new byte[size];
  }
  ~buffer() {
    delete []buf;
  }
};

typedef struct {
  WORD    bfType;
  DWORD   bfSize;
  WORD    bfReserved1;
  WORD    bfReserved2;
  DWORD   bfOffBits;
} __attribute((packed)) BITMAPFILEHEADER;
typedef struct {
  DWORD  biSize;
  DWORD   biWidth;
  DWORD   biHeight;
  WORD   biPlanes;
  WORD   biBitCount;
  DWORD  biCompression;
  DWORD  biSizeImage;
  DWORD   biXPelsPerMeter;
  DWORD   biYPelsPerMeter;
  DWORD  biClrUsed;
  DWORD  biClrImportant;
} __attribute((packed)) BITMAPINFOHEADER;
// Texture IDs
extern unsigned int wall,ground,jetpack,key,gr,hudh,font;
extern int w,h;

void LoadTextures();
void initGL();
void swapBuffers();
#endif

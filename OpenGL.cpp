#include "OpenGL.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <sstream>

unsigned int wall,ground,jetpack,key,gr,hudh,font;
struct MyFile {
  char const *filename;
  FILE *f;
  MyFile(char const *filename) : filename(filename) {
    if (!(f = fopen(filename,"rb")))
      throw std::runtime_error(std::string("Can't open file") + std::string(filename));
  }
  void read(void *buf, int size, size_t cnt) {
    if (fread(buf, size, cnt, f) != cnt)
      throw std::runtime_error(std::string("Error reading file ") + std::string(filename));
  }
  ~MyFile() {
    fclose(f);
  }
};
#define MgFilter GL_LINEAR
#define MpFilter GL_LINEAR_MIPMAP_LINEAR
#define MnFilter GL_LINEAR
void TexParams(bool mipmap) {
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,mipmap ? MpFilter : MnFilter);
}
void LoadBMP(char const *filename)
{
  BITMAPFILEHEADER fle;
  BITMAPINFOHEADER inf;
  MyFile f(filename);
  f.read(&fle,1,sizeof(fle));
  if (fle.bfType != 19778) {
    std::stringstream ss;
    ss << "LoadBMP_A: bfType "<< fle.bfType << " is incorrect in " << filename;
    throw std::runtime_error(ss.str());
  }
  fseek(f.f,0x0e,SEEK_SET);
  f.read(&inf,1,sizeof(inf));
  fseek(f.f,fle.bfOffBits,SEEK_SET);
  int w = inf.biWidth;
  int h = inf.biHeight;
  int bp = inf.biBitCount>>3;
  int bb = w*bp;
  if (inf.biBitCount != 24) {
    std::stringstream ss;
    ss << "LoadBMP_A: BitDepth " << inf.biBitCount << " is incorrect in " << filename;
    throw std::runtime_error(ss.str());
  }
  buffer vbuf(bb*h);
  byte *buf = vbuf.buf;
  f.read(buf,h,bb);
  buffer pbuf(w*h*3);
  byte *Surf = pbuf.buf;
  int x;
  int l;
  int b;
  for (int i = 0;i<(h);i++)
  {
    l = 0;
    b = 0;
    for (x = 0;x<w;x++) {Surf[l] = buf[b+2]; Surf[l+1] = buf[b+1]; Surf[l+2] = buf[b]; l+= 3; b+=3;}
    Surf+= w*3;
    buf += bb;
  }
  gluBuild2DMipmaps(GL_TEXTURE_2D,3,w,h,GL_RGB,GL_UNSIGNED_BYTE,pbuf.buf);
  TexParams(true);
}
void LoadBMP_A(char const *filename,byte r,byte g, byte b, bool mipmap)
{
  BITMAPFILEHEADER fle;
  BITMAPINFOHEADER inf;
  MyFile f(filename);
  f.read(&fle,1,sizeof(fle));
  if (fle.bfType != 19778) {
    std::stringstream ss;
    ss << "LoadBMP_A: bfType "<< fle.bfType << " is incorrect in " << filename;
    throw std::runtime_error(ss.str());
  }
  fseek(f.f,0x0e,SEEK_SET);
  f.read(&inf,1,sizeof(inf));
  fseek(f.f,fle.bfOffBits,SEEK_SET);
  int w = inf.biWidth;
  int h = inf.biHeight;
  int bp = inf.biBitCount>>3;
  int bb = (((w*bp)+3) & ~3);
  if (inf.biBitCount != 24) {
    std::stringstream ss;
    ss << "LoadBMP_A: BitDepth " << inf.biBitCount << " is incorrect in " << filename;
    throw std::runtime_error(ss.str());
  }
  buffer vbuf(bb*h);
  byte *buf = vbuf.buf;
  f.read(buf,h,bb);
  buffer pbuf(w*h*4);
  byte *Surf = pbuf.buf;
  int x;
  int l;
  int p;
  for (int i = 0;i<(h);i++)
  {
    l = 0;
    p = 0;
    for (x = 0;x<w;x++) {Surf[l] = r; Surf[l+1] = g; Surf[l+2] = b; Surf[l+3] = buf[p+2]; l+= 4; p+=3;}
    Surf+= w*4;
    buf += bb;
  }
  if (mipmap)
    gluBuild2DMipmaps(GL_TEXTURE_2D,4,w,h,GL_RGBA,GL_UNSIGNED_BYTE,pbuf.buf);
  else
    glTexImage2D(GL_TEXTURE_2D,0,4,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,pbuf.buf);
  TexParams(mipmap);
}
void LoadTextures()
{
    glGenTextures(1,&wall);
    glGenTextures(1,&ground);
    glGenTextures(1,&jetpack);
    glGenTextures(1,&key);
    glGenTextures(1,&hudh);
    glGenTextures(1,&font);

    glBindTexture(GL_TEXTURE_2D,wall);
    LoadBMP("wl.bmp");
    glBindTexture(GL_TEXTURE_2D,ground);
    LoadBMP("grnd.bmp");
    glBindTexture(GL_TEXTURE_2D,jetpack);
    LoadBMP("jetp.bmp");
    glBindTexture(GL_TEXTURE_2D,key);
    LoadBMP_A("key.bmp",255,255,0, true);
    glBindTexture(GL_TEXTURE_2D,hudh);
    LoadBMP_A("hud-h.bmp",255,0,0, false);
    glBindTexture(GL_TEXTURE_2D,font);
    LoadBMP_A("smallfont.bmp",255,255,255, false);
    glBindTexture(GL_TEXTURE_2D,gr);
    LoadBMP("gr.bmp");

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
SDL_Window *surf;
SDL_GLContext glctx;
void initGL()
{
  if(SDL_Init(SDL_INIT_VIDEO)<0)
    throw std::runtime_error(std::string("SDL initialization failed: ") + std::string(SDL_GetError()));

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  if((surf=SDL_CreateWindow("Maze3D",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             1920, 1080,
                             SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL))==0)
    throw std::runtime_error(std::string("Video init failed: ") + std::string(SDL_GetError()));
  glctx = SDL_GL_CreateContext(surf);
  SDL_GL_GetDrawableSize(surf,&w,&h);
  SDL_GL_SetSwapInterval(1);
  SDL_SetRelativeMouseMode(SDL_TRUE);

  glClearDepth( 1.0 );
  glClearColor(0.6f,0.8f,0.9f,1);

  glEnable(GL_DEPTH_TEST);
  float color[4] = {0.6f,0.8f,0.9f,1};
  glMatrixMode( GL_PROJECTION );
  gluPerspective( 50, (float)w/h, 0.05, 100 );
  glMatrixMode( GL_MODELVIEW );
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(8);
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE,GL_EXP2);
  glFogf(GL_FOG_DENSITY,0.025F);
  glFogfv(GL_FOG_COLOR,(float*)&color);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
void swapBuffers() {
  SDL_GL_SwapWindow(surf);
}

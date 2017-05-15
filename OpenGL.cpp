#include "OpenGL.h"
#include <stdio.h>
#include <SDL/SDL.h>
#include <vector>

Pict *wl;
unsigned int wall,ground,jetpack,key,gr,hudh,font;

int LoadBMP(char const *filename,Pict *&surf)
{
  surf = new Pict;
  FILE *f;
  BITMAPFILEHEADER fle;
  BITMAPINFOHEADER inf;
  if (!(f = fopen(filename,"rb"))) {fprintf(stderr,"LoadBMP: Can't open %s\n",filename);return 0;}
  fread(&fle,1,sizeof(fle),f);
  if (fle.bfType != 19778) {fprintf(stderr,"LoadBMP: bfType %i is incorrect in %s\n",fle.bfType,filename);return 0;}
  fseek(f,0x0e,SEEK_SET);
  fread(&inf,1,sizeof(inf),f);
  fseek(f,fle.bfOffBits,SEEK_SET);
  int w = inf.biWidth;
  int h = inf.biHeight;
  int bp = inf.biBitCount>>3;
  int bb = w*bp;
  if (inf.biBitCount != 24){fprintf(stderr,"LoadBMP: BitDepth %i is incorrect in %s\n",inf.biBitCount,filename);
   return 0;}
  std::vector<byte> vbuf(bb*h);
  byte *buf = &vbuf[0];
  int ri=fread(buf,h,bb,f);
  if (ri!=bb)
  { fprintf(stderr,"warning: only %i lines was read from %s\n",ri,filename);
  }
  surf->w = w;
  surf->h = h;
  surf->data = new byte[w*h*3];
  byte *Surf = surf->data;
  int x;
  int l;
  int b;
  for (int i = 0;i<(h);i++)
  {
    l = 0;
    b = 0;
    for (x = 0;x<w;x++){Surf[l] = buf[b+2]; Surf[l+1] = buf[b+1]; Surf[l+2] = buf[b]; l+= 3; b+=3;}
    Surf+= w*3;
    buf += bb;
  }
  return 1;
}
int LoadBMP_A(char const *filename,Pict *&surf,byte r,byte g, byte b)
{
  surf = new Pict;
  FILE *f;
  BITMAPFILEHEADER fle;
  BITMAPINFOHEADER inf;
  if (!(f = fopen(filename,"rb"))) {fprintf(stderr,"LoadBMP_A: Can't open %s\n",filename);return 0;}
  fread(&fle,1,sizeof(fle),f);
  if (fle.bfType != 19778) return 0;
  fseek(f,0x0e,SEEK_SET);
  fread(&inf,1,sizeof(inf),f);
  fseek(f,0x36/*fle.bfOffBits*/,SEEK_SET);
  int w = inf.biWidth;
  int h = inf.biHeight;
  int bp = inf.biBitCount>>3;
  int bb = (((w*bp)+3) & ~3);
  if (inf.biBitCount != 24) return 0;
  byte *buf = new byte[bb*h];
  fread(buf,h,bb,f);
  surf->w = w;
  surf->h = h;
  surf->data = new byte[w*h*4];
  byte *Surf = surf->data;
  int x;
  int l;
  int p;
//  buf += bb*(h-1);
  for (int i = 0;i<(h);i++)
  {
    l = 0;
    p = 0;
    for (x = 0;x<w;x++) {Surf[l] = r; Surf[l+1] = g; Surf[l+2] = b; Surf[l+3] = buf[p+2]; l+= 4; p+=3;}
    Surf+= w*4;
    buf += bb;
  }
//delete buf;
  return 1;
}
#define MgFilter GL_LINEAR
#define MpFilter GL_LINEAR_MIPMAP_LINEAR
#define MnFilter GL_LINEAR
int LoadTextures()
{
    glGenTextures(1,&wall);
    glGenTextures(1,&ground);
    glGenTextures(1,&jetpack);
    glGenTextures(1,&key);
    glGenTextures(1,&hudh);
    glGenTextures(1,&font);
    glBindTexture(GL_TEXTURE_2D,wall);

    if (!LoadBMP("wl.bmp",wl)){fprintf(stderr,"ERROR!!!\n");return 0;}
 //   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

    gluBuild2DMipmaps(GL_TEXTURE_2D,3,wl->w,wl->h,GL_RGB,GL_UNSIGNED_BYTE,wl->data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MpFilter);

    delete[] wl->data;
    delete wl;
    LoadBMP("grnd.bmp",wl);

    glBindTexture(GL_TEXTURE_2D,ground);

    gluBuild2DMipmaps(GL_TEXTURE_2D,3,wl->w,wl->h,GL_RGB,GL_UNSIGNED_BYTE,wl->data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MpFilter);

    delete wl->data;
    delete wl;

    LoadBMP("jetp.bmp",wl);

    glBindTexture(GL_TEXTURE_2D,jetpack);

    gluBuild2DMipmaps(GL_TEXTURE_2D,3,wl->w,wl->h,GL_RGB,GL_UNSIGNED_BYTE,wl->data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MpFilter);

    delete wl->data;
    delete wl;

    LoadBMP_A("key.bmp",wl,255,255,0);

    glBindTexture(GL_TEXTURE_2D,key);

    glTexImage2D (GL_TEXTURE_2D,0,4,wl->w,wl->h,0,GL_RGBA,GL_UNSIGNED_BYTE,wl->data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MnFilter);

    delete wl->data;
    delete wl;

    LoadBMP_A("hud-h.bmp",wl,255,0,0);

    glBindTexture(GL_TEXTURE_2D,hudh);

    glTexImage2D (GL_TEXTURE_2D,0,4,wl->w,wl->h,0,GL_RGBA,GL_UNSIGNED_BYTE,wl->data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MnFilter);

    delete wl->data;
    delete wl;

    LoadBMP_A("smallfont.bmp",wl,255,255,255);

    glBindTexture(GL_TEXTURE_2D,font);

    glTexImage2D (GL_TEXTURE_2D,0,4,wl->w,wl->h,0,GL_RGBA,GL_UNSIGNED_BYTE,wl->data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MnFilter);

    delete wl->data;
    delete wl;

    LoadBMP("gr.bmp",wl);

    glBindTexture(GL_TEXTURE_2D,gr);

    gluBuild2DMipmaps(GL_TEXTURE_2D,4,wl->w,wl->h,GL_RGB,GL_UNSIGNED_BYTE,wl->data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,MgFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,MpFilter);

    delete wl->data;
    delete wl;

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    return 1;
}
int initGL()
{
  if(SDL_Init(SDL_INIT_VIDEO)<0)
  {
    fprintf(stderr, "SDL initialization failed: %s\n",SDL_GetError());
    return FALSE;
  }

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  SDL_Surface *surf;
  if((surf=SDL_SetVideoMode(0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN))==0)
  {
    fprintf(stderr, "Video init failed: %s\n", SDL_GetError());
    return FALSE;
  }
  w = surf->w;
  h = surf->h;
  SDL_ShowCursor(0);
  SDL_WarpMouse(w/2,h/2);

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
  return 1;
}

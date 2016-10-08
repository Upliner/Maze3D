#ifndef LEVEL3D_H
#define LEVEL3D_H
#include "defines.h"
struct tile
{
  byte type;
  byte vx,vy;
  bool dst;
};

extern float xc, yc, zc, xi, yi, zi, xr,yr;
extern double xri,yri;
typedef tile TLine[80];
extern TLine Level[50];
extern float FloorZ,CeilZ;
extern byte health;
extern bool jet;
extern byte tr,tg,tb,ta;
extern word wallds,wlds_s;
void RenderLevel();
void ControlLevel();
void LoadLevel(char *filename);

#endif

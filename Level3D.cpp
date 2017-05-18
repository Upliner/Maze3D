#include <list>
#include "OpenGL.h"
#include "Common.h"
#include "Level3D.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef byte BLine[80];
TLine Level[50];
BLine Moved[50];
BLine Optim[50];
float xc=2,yc=2,zc=0, xi, yi, zi, xr,yr;
double xri,yri;
float FloorZ = 0,CeilZ = 1000000000;
byte health = 100;
#ifndef _DEBUG
bool jet = false;
#else
bool jet = true;
#endif
byte tr,tg=255,tb=0,ta=0;
word wallds,wlds_s = 0;
byte GetTile(int x,int y)
{ if (x<0||y<0||x>79||y>49) return 255;
  return Level[y][x].type;
}
void DrawObject(double x,double y,double z,word id,byte alpha = 255)
{ glPushMatrix();
  glTranslated(-x, z, -y);
  glColor4ub(255,255,255,alpha);
  glCallList(id);
  glPopMatrix();
}
void DrawLevelTile(int x,int y)
{ switch (Level[y][x].type)
  { case 1: DrawObject((x<<1)+2,(y<<1)+2,0,Optim[y][x]==1?BOX_OPTIM_CEILONLY:BOX);break;
    case 2: DrawObject((x<<1)+2,(y<<1)+2,-(Moved[y][x]*0.0625),Optim[y][x]==1?BOX_OPTIM_CEILONLY:BOX,Moved[y][x]>24?(255-(Moved[y][x]<<5)):255);break;
    case 4: DrawObject((x<<1)+2,(y<<1)+2,0,JETPACK);break;
    case 5: DrawObject((x<<1)+2,(y<<1)+2,0,WALLD);break;
    case 6: DrawObject((x<<1)+2,(y<<1)+2,Moved[y][x]*0.2375,ONEPASS); if (Moved[y][x]) DrawObject((x<<1)+2,(y<<1)+2,(Moved[y][x]*0.25)-2,BOX);break;
    case 7: DrawObject((x<<1)+2,(y<<1)+2,-(Moved[y][x]*0.0625),DOOR);break;
    case 8: DrawObject((x<<1)+2,(y<<1)+2,0,KEY);break;
    case 9: DrawObject((x<<1)+2,(y<<1)+2,-(Moved[y][x]*0.02),BUTTON);break;
    case 10: DrawObject((x<<1)+2,(y<<1)+2,0,TELEPORTER);break;
    case 12: DrawObject((x<<1)+2,(y<<1)+2,-1.75,TRAP);break;
    case 13: DrawObject((x<<1)+2,(y<<1)+2,-1.75,TRAP);break;
    case 14: DrawObject((x<<1)+2,(y<<1)+2,0,TW);break;
    case 15: DrawObject((x<<1)+2,(y<<1)+2,0,GR);break;
    case 16: DrawObject((x<<1)+2,(y<<1)+2,2,GR);break;
    case 17: DrawObject((x<<1)+2,(y<<1)+2,0,BOX); DrawObject((x<<1)+2,(y<<1)+2,2,GR);break;
    case 100: DrawObject((x<<1)+2,(y<<1)+2,0,EXIT);break;
    case 130: DrawObject((x<<1)+2,(y<<1)+2,0,TRAP);break;
  }
}
int TLevel(byte x,byte y)
{ switch (Level[y][x].type)
  { case 14: return 2;
    case 16: return 2;
    case 17: return 2;
    case  1: return 1;
    case  2: return Moved[y][x]==0?1:0;
    default:return 0;
  }
}
void RenderLevel()
{ glCallList(FLOOR);
  glCallList(EXTWALL);
  int x = (int)((xc-1)*0.5),y = (int)((yc-1)*0.5);
  int xm,ym;
  for (ym=max(0,(byte)y-41);ym<=min(49,(byte)y+41);ym++)
    for (xm=max(0,(byte)x-41);xm<=min(79,(byte)x+41);xm++)
      DrawLevelTile(xm,ym);
}
struct movstruct
{
  int x,y;
  movstruct(int _x,int _y) : x(_x), y(_y) {}
//  int mov;
};
std::list<movstruct> movs;
void ProcessMoving()
{
  int xf,yf;
  for (std::list<movstruct>::iterator i = movs.begin();i!=movs.end();++i)
  {
    xf = i->x;
    yf = i->y;
    switch (Level[yf][xf].type)
    { case 2:
        if (Moved[yf][xf]>0)
        { Moved[yf][xf]++;
          if (Moved[yf][xf] == 32)
          { Moved[yf][xf] = 0;
            Level[yf][xf].type = 0;
            i=movs.erase(i);
            continue;
          }
        }
        break;
      case 6:
        if (Moved[yf][xf]>0)
        { Moved[yf][xf]++;
          if (Moved[yf][xf] == 8)
          { Moved[yf][xf] = 0;
            Level[yf][xf].type = 1;
            Optim[yf][xf] = 0;
            i=movs.erase(i);
            continue;
          }
        }
        break;
      case 7: if(Moved[yf][xf]>0){if(Moved[yf][xf]<31)Moved[yf][xf]++;else{i=movs.erase(i);continue;}} break;
      case 9: if(Moved[yf][xf]>0){if(Moved[yf][xf]<8 )Moved[yf][xf]++;else{i=movs.erase(i);continue;}} break;

    }
  }
}
void Unoptim(int x,int y)
{
  if (x>0) Optim[y][x-1]=0;
  if (y>0) Optim[y-1][x]=0;
  if (x<79) Optim[y][x+1]=0;
  if (y<49) Optim[y+1][x]=0;
}
void StartMov(int x,int y)
{
  Moved[y][x]=1;
  movs.push_back(movstruct(x, y));
}
void DestroyWall(int x,int y)
{
  Level[y][x].type=2;
  StartMov(x, y);
  Unoptim(x, y);
}
bool CheckWall(int xf, int yf, float x, float y)
{
  if (xf<0||yf<0||xf>79||yf>49) return false;
  if (((x+xi*0.5)>xf-0.6)&&((x+xi*0.5)<xf+0.6)&&((y+yi*0.5)>yf-0.6)&&((y+yi*0.5)<yf+0.6))
  { if (Level[yf][xf].type == 15&&(zc>=FloorZ)){CeilZ = min(CeilZ,0.8f);}
    if (Level[yf][xf].type == 16&&(zc>=FloorZ)){CeilZ = min(CeilZ,2.8f);}
    if (Level[yf][xf].type == 1||Level[yf][xf].type == 2||Level[yf][xf].type == 14||Level[yf][xf].type == 17||(Level[yf][xf].type == 7&&Moved[yf][xf]!=31))
    { if ((Level[yf][xf].type == 2)&&(Moved[yf][xf] == 0)) DestroyWall(xf,yf);
      if ((Level[yf][xf].type == 7)&&Level[yf][xf].dst&&(Moved[yf][xf] == 0)) StartMov(xf,yf);
      if(x<=xf-0.599){xc=(float)((xf-0.6)*2)+2; xi = 0; return true;}
      if(x>=xf+0.599){xc=(float)((xf+0.6)*2)+2; xi = 0; return true;}
      if(y<=yf-0.599){yc=(float)((yf-0.6)*2)+2; yi = 0; return true;}
      if(y>=yf+0.599){yc=(float)((yf+0.6)*2)+2; yi = 0; return true;}
      if ((Moved[yf][xf] == 0)||(Level[yf][xf].type != 2&&Level[yf][xf].type != 7)) {FloorZ = max(FloorZ,2);} else {if(FloorZ==0)FloorZ = (float)(2-(Moved[yf][xf]*0.0625));}
      if (Level[yf][xf].type == 14){FloorZ = max(FloorZ,4);}
    }
  }
  return false;
}
bool CheckTallWall(int xf, int yf, float x, float y)
{ if (xf<0||yf<0||xf>79||yf>49) return false;
  if (((x+xi*0.5)>xf-0.6)&&((x+xi*0.5)<xf+0.6)&&((y+yi*0.5)>yf-0.6)&&((y+yi*0.5)<yf+0.6))
  { if ( Level[yf][xf].type == 1 ||Level[yf][xf].type == 15 ||Level[yf][xf].type == 17){FloorZ = max(FloorZ,2);}
    if ((Level[yf][xf].type == 16||Level[yf][xf].type == 17)&&(zc>=FloorZ)){CeilZ = min(CeilZ,2.8f);}
    if (Level[yf][xf].type == 14)
    { if(x<xf-0.599){xc=(float)((xf-0.6)*2)+2; xi = 0; return true;}
      if(x>xf+0.599){xc=(float)((xf+0.6)*2)+2; xi = 0; return true;}
      if(y<yf-0.599){yc=(float)((yf-0.6)*2)+2; yi = 0; return true;}
      if(y>yf+0.599){yc=(float)((yf+0.6)*2)+2; yi = 0; return true;}
    }
  }
}

void ControlLevel()
{
  int xf,yf;
  ProcessMoving();
  if (wlds_s>0&&wlds_s<11)wlds_s++;if(wlds_s>11&&wlds_s<22)wlds_s++;
  if(wlds_s==22){if(wallds==0){wlds_s=0;}else{wlds_s=1;}}
  if(ta)ta=ta<8?0:ta-8;
  if (xc<  1.2F) {xc =   1.2F;xi = 0;} if (yc<  1.2F) {yc =   1.2F; yi = 0;}
  if (xc>160.8F) {xc = 160.8F;xi = 0;} if (yc>100.8F) {yc = 100.8F; yi = 0;}
  double x = (xc-xi-2)*0.5,y = (yc-yi-2)*0.5;
  xf=(int)(x+0.5);yf=(int)(y+0.5);
  if (wallds&&wlds_s == 16&&zc<0.2)
  {
    int xm = xf+(int)floor(xri+0.5),ym = yf+(int)floor(yri+0.5);
    if (GetTile(xm,ym)==1)
    {wallds--;DestroyWall(xm,ym);}
  }
  if ((zc<1.7)&&(Level[yf][xf].type == 6))
  { tr=255;tg=255;tb=0;ta=64;
    if (!Moved[yf][xf]) {
      if ((int)(x-xi+0.5)<xf){for (;Level[yf][xf].type==6;xf++)StartMov(xf,yf);xc=(float)((xf+1)*2);zc=(Level[yf][xf].type==1)?2.0f:0.0f;return;}
      if ((int)(x-xi+0.5)>xf){for (;Level[yf][xf].type==6;xf--)StartMov(xf,yf);xc=(float)((xf+1)*2);zc=(Level[yf][xf].type==1)?2.0f:0.0f;return;}
      if ((int)(y-yi+0.5)<yf){for (;Level[yf][xf].type==6;yf++)StartMov(xf,yf);yc=(float)((yf+1)*2);zc=(Level[yf][xf].type==1)?2.0f:0.0f;return;}
      if ((int)(y-yi+0.5)>yf){for (;Level[yf][xf].type==6;yf--)StartMov(xf,yf);yc=(float)((yf+1)*2);zc=(Level[yf][xf].type==1)?2.0f:0.0f;return;}
    } else {
      FloorZ = max(FloorZ, 0.25 * Moved[yf][xf]);
    }
  }
  if ((zc<0.2)&&(Level[yf][xf].type == 5)){Level[yf][xf].type = 0; wallds++;if (wlds_s == 0) wlds_s = 1;}
  if ((zc<1.7)&&(Level[yf][xf].type == 100)) {fprintf(stderr,"you win"); quit(0);}
  if ((Level[yf][xf].type == 11)&&jet){jet=false;if(zc>FloorZ){xi=0;yi=0;}if (zi>0)zi=-0.05f;}
  if ((zc<1.7)&&(Level[yf][xf].type == 10))
  {xc=(float)Level[yf][xf].vx*2;yc=(float)Level[yf][xf].vy*2;zc=(Level[Level[yf][xf].vy-1][Level[yf][xf].vx-1].type)==1?2.0f:0.0f;tr=0;tb=0;tg=255;ta=255;xi=0;yi=0;zi=0;return;}
  if ((zc<1.7)&&(Level[yf][xf].type == 3||Level[yf][xf].type == 12)){Level[yf][xf].type=130;health=0;jet=false;wallds=0;wlds_s=0;zc+=1;xi*=0.1f;yi*=0.1f;zi=0.1f;}
  if ((zc<0.2)&&(Level[yf][xf].type == 4)&&((x>xf-0.2)&&(x<xf+0.2)&&(y>yf-0.2)&&(y<yf+0.2))){jet=true; Level[yf][xf].type = 0;}
  if ((zc<0.2)&&(Level[yf][xf].type == 8)&&((x>xf-0.2)&&(x<xf+0.2)&&(y>yf-0.2)&&(y<yf+0.2)))
  { Level[yf][xf].type = 0; Level[Level[yf][xf].vy-1][Level[yf][xf].vx-1].dst = 1;}
  if ((zc<0.2)&&(Level[yf][xf].type == 9)&&(Moved[yf][xf] == 0)&&((x>xf-0.3)&&(x<xf+0.3)&&(y>yf-0.3)&&(y<yf+0.3)))
  { DestroyWall(Level[yf][xf].vx-1,Level[yf][xf].vy-1);
    StartMov(xf,yf);
  }
  if (zc>=FloorZ) FloorZ = 0;
  CeilZ = 1000000000;
  if (zc<2)
  {
    xf = (int)(x+0.5);yf = (int)(y+0.5);
    bool coll = false;
    CheckWall(xf, yf, x, y);
    coll |= CheckWall(xf-1, yf, x, y);
    coll |= CheckWall(xf+1, yf, x, y);
    coll |= CheckWall(xf, yf-1, x, y);
    coll |= CheckWall(xf, yf+1, x, y);
    if (!coll) {
      CheckWall(xf-1, yf-1, x, y);
      CheckWall(xf+1, yf-1, x, y);
      CheckWall(xf-1, yf+1, x, y);
      CheckWall(xf+1, yf+1, x, y);
    }
    if ((Level[yf][xf].type == 9)&&((x>xf-0.3)&&(x<xf+0.3)&&(y>yf-0.3)&&(y<yf+0.3))){FloorZ = (float)(0.2-(Moved[yf][xf]*0.02));}
  } else
  { if (zc<4)
    {
      xf = (int)(x+0.5);yf = (int)(y+0.5);
      bool coll = false;
      CheckTallWall(xf, yf, x, y);
      coll |= CheckTallWall(xf-1, yf, x, y);
      coll |= CheckTallWall(xf+1, yf, x, y);
      coll |= CheckTallWall(xf, yf-1, x, y);
      coll |= CheckTallWall(xf, yf+1, x, y);
      if (!coll) {
        CheckTallWall(xf-1, yf-1, x, y);
        CheckTallWall(xf+1, yf-1, x, y);
        CheckTallWall(xf-1, yf+1, x, y);
        CheckTallWall(xf+1, yf+1, x, y);
      }
    } else
    { x += xi * 0.5; y += yi * 0.5;
      for (yf = (int)y-1;yf<=(int)y+1;yf++)
        for (xf = (int)x-1;xf<=(int)x+1;xf++)
        { if (xf<0||yf<0||xf>79||yf>49) continue;
          if ((x>xf-0.6)&&(x<xf+0.6)&&(y>yf-0.6)&&(y<yf+0.6))
          { if (Level[yf][xf].type == 1 ||Level[yf][xf].type == 15){FloorZ = max(FloorZ,2);}
            if (Level[yf][xf].type == 14||Level[yf][xf].type == 16||Level[yf][xf].type == 17){FloorZ = max(FloorZ,4);}
          }
        }
    }
  }
}
int TALevel(int x,int y)
{
  if (x<0||x>=80||y<0||y>=50) return 2;
  return TLevel(x,y);
}
void CreateOptim()
{
  int x,y,i;
  for(y=0;y<50;y++)
    for(x=0;x<80;x++)
    {
      i = TALevel(x,y);
      if (TALevel(x-1,y)>=i&&TALevel(x+1,y)>=i&&TALevel(x,y-1)>=i&&TALevel(x,y+1)>=i)
        Optim[y][x]=1; else Optim[y][x]=0;
    }
}

void LoadLevel(char *filename)
{
  FILE *f = fopen(filename,"rb");
  word m;
  fread(&Level,sizeof(tile),4000,f);
  fread(&m,2,1,f);m--;
  Level[m/80][m%80].type=100;
  ZeroMemory(Moved,4000);
  movs.clear();
  CreateOptim();
  wallds=0;ta=0;
  fclose(f);
}

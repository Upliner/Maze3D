#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#include "Common.h"
#include "OpenGL.h"
#include "input.h"
#include "Level3D.h"
#define Interval 30

char *mapname=(char*)"1.map";
dword t1,t2,ti;
int w,h;
void createObjects()
{ double x,y;
  glNewList(BOX, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,wall);
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(0,0);glVertex3i(-1,-1,-1);glTexCoord2s(0,1);glVertex3i(-1,+1,-1);
      glTexCoord2s(1,0);glVertex3i(+1,-1,-1);glTexCoord2s(1,1);glVertex3i(+1,+1,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(1,0);glVertex3i(-1,-1,+1);glTexCoord2s(0,0);glVertex3i(+1,-1,+1);
      glTexCoord2s(1,1);glVertex3i(-1,+1,+1);glTexCoord2s(0,1);glVertex3i(+1,+1,+1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(1,0);glVertex3i(+1,-1,+1);glTexCoord2s(0,0);glVertex3i(+1,-1,-1);
      glTexCoord2s(1,1);glVertex3i(+1,+1,+1);glTexCoord2s(0,1);glVertex3i(+1,+1,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(0,0);glVertex3i(-1,-1,+1);glTexCoord2s(0,1);glVertex3i(-1,+1,+1);
      glTexCoord2s(1,0);glVertex3i(-1,-1,-1);glTexCoord2s(1,1);glVertex3i(-1,+1,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(0,0);glVertex3i(-1,+1,-1);glTexCoord2s(1,0);glVertex3i(-1,+1,+1);
      glTexCoord2s(0,1);glVertex3i(+1,+1,-1);glTexCoord2s(1,1);glVertex3i(+1,+1,+1);
    glEnd();
  glEndList();

  glNewList(BOX_OPTIM_CEILONLY, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,wall);
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(0,0);glVertex3i(-1,+1,-1);glTexCoord2s(1,0);glVertex3i(-1,+1,+1);
      glTexCoord2s(0,1);glVertex3i(+1,+1,-1);glTexCoord2s(1,1);glVertex3i(+1,+1,+1);
    glEnd();
  glEndList();


  glNewList(FLOOR, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ground);
    glDisable(GL_CULL_FACE);
    glColor3ub(255,255,255);
    for (y=2;y>-104;y-=6.625)
    { glBegin(GL_TRIANGLE_STRIP);
      for (x=2;x>=-164;x-=10.375)
      { glTexCoord2d(x,5);glVertex3d(x,-1,y-6.625);
        glTexCoord2d(x,0);glVertex3d(x,-1,y      );
      }
      glEnd();
    }
    glEnable(GL_CULL_FACE);
  glEndList();

  glNewList(EXTWALL, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,wall);
    glBegin(GL_QUADS);
      glTexCoord2s( 0,0); glVertex3i(   1,3, 1); glTexCoord2s( 0,1); glVertex3i(   1,3,-1);
      glTexCoord2s(82,1); glVertex3i(-163,3,-1); glTexCoord2s(82,0); glVertex3i(-163,3, 1);

      glTexCoord2s( 0,2); glVertex3i(  -1, 3,-1); glTexCoord2s( 0,0); glVertex3i(  -1,-1,-1);
      glTexCoord2s(80,0); glVertex3i(-161,-1,-1); glTexCoord2s(80,2); glVertex3i(-161 ,3,-1);

      glTexCoord2s( 0, 0); glVertex3i(   1,3,-101); glTexCoord2s( 0, 1); glVertex3i(   1,3,-103);
      glTexCoord2s(82, 1); glVertex3i(-163,3,-103); glTexCoord2s(82, 0); glVertex3i(-163,3,-101);

      glTexCoord2s(80, 2); glVertex3i(  -1, 3,-101); glTexCoord2s( 0, 2); glVertex3i(-161 ,3,-101);
      glTexCoord2s( 0, 0); glVertex3i(-161,-1,-101); glTexCoord2s(80, 0); glVertex3i(  -1,-1,-101);

      glTexCoord2s(0, 0); glVertex3i( 1,3,  -1); glTexCoord2s(0,50); glVertex3i( 1,3,-101);
      glTexCoord2s(1,50); glVertex3i(-1,3,-101); glTexCoord2s(1, 0); glVertex3i(-1,3,  -1);

      glTexCoord2s(50,2); glVertex3i(-1, 3,  -1); glTexCoord2s( 0,2); glVertex3i(-1, 3,-101);
      glTexCoord2s( 0,0); glVertex3i(-1,-1,-101); glTexCoord2s(50,0); glVertex3i(-1,-1,  -1);

      glTexCoord2s(0, 0); glVertex3i(-161,3,  -1); glTexCoord2s(0,50); glVertex3i(-161,3,-101);
      glTexCoord2s(1,50); glVertex3i(-163,3,-101); glTexCoord2s(1, 0); glVertex3i(-163,3,  -1);

      glTexCoord2s( 0,2); glVertex3i(-161, 3,  -1); glTexCoord2s( 0,0); glVertex3i(-161,-1,  -1);
      glTexCoord2s(50,0); glVertex3i(-161,-1,-101); glTexCoord2s(50,2); glVertex3i(-161, 3,-101);
    glEnd();
  glEndList();

  glNewList(JETPACK, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,jetpack);
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(0,0);glVertex3d(-0.2,-0.9,-0.2);glTexCoord2s(1,0);glVertex3d(-0.2,-0.9,+0.2);
      glTexCoord2s(0,1);glVertex3d(+0.2,-0.9,-0.2);glTexCoord2s(1,1);glVertex3d(+0.2,-0.9,+0.2);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(0,0);glVertex3d(+0.2,  -1,+0.2);glTexCoord2s(1,0);glVertex3d(+0.2,  -1,-0.2);
      glTexCoord2s(0,0);glVertex3d(+0.2,-0.9,+0.2);glTexCoord2s(1,0);glVertex3d(+0.2,-0.9,-0.2);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2s(0,0);glVertex3d(-0.2,  -1,+0.2);glTexCoord2s(0,0);glVertex3d(-0.2,-0.9,+0.2);
      glTexCoord2s(1,0);glVertex3d(-0.2,  -1,-0.2);glTexCoord2s(1,0);glVertex3d(-0.2,-0.9,-0.2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLE_STRIP);
      glColor3ub(160,160,160);
      glVertex3d(-0.2,  -1,-0.2);glVertex3d(-0.2,-0.9,-0.2);glVertex3d(+0.2,  -1,-0.2);glVertex3d(+0.2,-0.9,-0.2);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glVertex3d(-0.2,  -1,+0.2);glVertex3d(+0.2,  -1,+0.2);glVertex3d(-0.2,-0.9,+0.2);glVertex3d(+0.2,-0.9,+0.2);
    glEnd();
  glEndList();

  glNewList(TRAP, GL_COMPILE);
    glDisable(GL_TEXTURE_2D);
    for (y = -0.8;y<=0.8;y+=0.4)
      for (x = -0.8;x<=0.8;x+=0.4)
        { glBegin(GL_TRIANGLE_FAN);
          glColor3ub(100,  0,  0);glVertex3d(x,0.9,y);
          glColor3ub(192,180,180);glVertex3d(x-0.1,-1,y-0.1);
          glColor3ub(160,160,160);glVertex3d(x-0.1,-1,y+0.1);
          glColor3ub(128,128,128);glVertex3d(x+0.1,-1,y+0.1);
          glColor3ub(141,141,141);glVertex3d(x+0.1,-1,y-0.1);
          glColor3ub(192,180,180);glVertex3d(x-0.1,-1,y-0.1);
          glEnd();
        }
  glEndList();

  glNewList(BUTTON, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,wall);
    glBegin(GL_QUADS);
      glTexCoord2d(0,0);glVertex3d(-0.3,-0.8,-0.3);glTexCoord2d(1,0);glVertex3d(-0.3,-0.8,+0.3);
      glTexCoord2d(1,1);glVertex3d(+0.3,-0.8,+0.3);glTexCoord2d(0,1);glVertex3d(+0.3,-0.8,-0.3);
      glTexCoord2d(0,0);glVertex3d(+0.3,  -1,+0.3);glTexCoord2d(1,0);glVertex3d(+0.3,  -1,-0.3);
      glTexCoord2d(1,0.1);glVertex3d(+0.3,-0.8,-0.3);glTexCoord2d(0,0.1);glVertex3d(+0.3,-0.8,+0.3);
      glTexCoord2d(0,0);glVertex3d(-0.3,  -1,+0.3);glTexCoord2d(0.1,0);glVertex3d(-0.3,-0.8,+0.3);
      glTexCoord2d(0.1,1);glVertex3d(-0.3,-0.8,-0.3);glTexCoord2d(0,1);glVertex3d(-0.3,  -1,-0.3);

      glTexCoord2d(0,0);glVertex3d(-0.3,  -1,-0.3);glTexCoord2d(0.1,0);glVertex3d(-0.3,-0.8,-0.3);
      glTexCoord2d(0.1,1);glVertex3d(+0.3,-0.8,-0.3);glTexCoord2d(0,1);glVertex3d(+0.3,  -1,-0.3);
      glTexCoord2d(0,0);glVertex3d(-0.3,  -1,+0.3);glTexCoord2d(1,0);glVertex3d(+0.3,  -1,+0.3);
      glTexCoord2d(1,0.1);glVertex3d(+0.3,-0.8,+0.3);glTexCoord2d(0,0.1);glVertex3d(-0.3,-0.8,+0.3);
    glEnd();
  glEndList();

  glNewList(DOOR, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,wall);
    for (y = -0.8;y<=0.8;y+=0.4)
      for (x = -0.8;x<=0.8;x+=0.4)
      { glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0   ,0);glVertex3d(x-0.1,-1,y-0.1); glTexCoord2d(0   ,0.5);glVertex3d(x-0.1,+1,y-0.1);
        glTexCoord2d(0.05,0);glVertex3d(x+0.1,-1,y-0.1); glTexCoord2d(0.05,0.5);glVertex3d(x+0.1,+1,y-0.1);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0.05,0  );glVertex3d(x-0.1,-1,y+0.1); glTexCoord2d(0  ,0);glVertex3d(x+0.1,-1,y+0.1);
        glTexCoord2d(0.05,0.5);glVertex3d(x-0.1,+1,y+0.1); glTexCoord2d(0  ,0.5);glVertex3d(x+0.1,+1,y+0.1);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0.05,0  );glVertex3d(x+0.1,-1,y+0.1); glTexCoord2d(0  ,0);glVertex3d(x+0.1,-1,y-0.1);
        glTexCoord2d(0.05,0.5);glVertex3d(x+0.1,+1,y+0.1); glTexCoord2d(0  ,0.5);glVertex3d(x+0.1,+1,y-0.1);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0   ,0);glVertex3d(x-0.1,-1,y+0.1); glTexCoord2d(0   ,0.5);glVertex3d(x-0.1,+1,y+0.1);
        glTexCoord2d(0.05,0);glVertex3d(x-0.1,-1,y-0.1); glTexCoord2d(0.05,0.5);glVertex3d(x-0.1,+1,y-0.1);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(0,   0);glVertex3d(x-0.1,+1,y-0.1); glTexCoord2d(0.05,   0);glVertex3d(x-0.1,+1,y+0.1);
        glTexCoord2d(0,0.05);glVertex3d(x+0.1,+1,y-0.1); glTexCoord2d(0.05,0.05);glVertex3d(x+0.1,+1,y+0.1);
        glEnd();
      }
  glEndList();

  glNewList(KEY, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,key);
    glBegin(GL_TRIANGLE_STRIP);
//      glColor3ub(255,255,255);
      glTexCoord2d(0,0);glVertex3d(-0.2,-0.95,-0.2);glTexCoord2d(1,0);glVertex3d(-0.2,-0.95,+0.2);
      glTexCoord2d(0,1);glVertex3d(+0.2,-0.95,-0.2);glTexCoord2d(1,1);glVertex3d(+0.2,-0.95,+0.2);
    glEnd();
  glEndList();

  glNewList(TELEPORTER, GL_COMPILE);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glColor3ub(0,255,0);glVertex3d(-0.9,  -1,-0.9); glColor3ub(0,192,0); glVertex3d(-0.9,-0.9,-0.9); glVertex3d(+0.9,-0.9,-0.9);glColor3ub(0,255,0); glVertex3d(+0.9,  -1,-0.9);
      glVertex3d(-0.9,  -1,+0.9); glVertex3d(+0.9,  -1,+0.9); glColor3ub(0,192,0); glVertex3d(+0.9,-0.9,+0.9); glVertex3d(-0.9,-0.9,+0.9);
      glColor3ub(0,255,0);glVertex3d(+0.9,  -1,+0.9); glVertex3d(+0.9,  -1,-0.9); glColor3ub(0,192,0); glVertex3d(+0.9,-0.9,-0.9); glVertex3d(+0.9,-0.9,+0.9);
      glColor3ub(0,255,0);glVertex3d(-0.9,  -1,+0.9); glColor3ub(0,192,0); glVertex3d(-0.9,-0.9,+0.9); glVertex3d(-0.9,-0.9,-0.9); glColor3ub(0,255,0); glVertex3d(-0.9,  -1,-0.9);
      glColor3ub(0,192,0);glVertex3d(-0.9,-0.9,-0.9); glVertex3d(-0.9,-0.9,+0.9); glVertex3d(+0.9,-0.9,+0.9); glVertex3d(+0.9,-0.9,-0.9);
      glColor3ub(0,255,0);glVertex3d(-0.9,  -1,+0.9); glVertex3d(-0.9,  -1,-0.9); glVertex3d(+0.9,  -1,-0.9); glVertex3d(+0.9,  -1,+0.9);
    glEnd();
  glEndList();
  glNewList(ONEPASS, GL_COMPILE);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glColor3ub(255,255,0);glVertex3d(-0.9,  -1,-0.9); glColor3ub(192,192,0); glVertex3d(-0.9,-0.9,-0.9); glVertex3d(+0.9,-0.9,-0.9);glColor3ub(255,255,0); glVertex3d(+0.9,  -1,-0.9);
      glVertex3d(-0.9,  -1,+0.9); glVertex3d(+0.9,  -1,+0.9); glColor3ub(192,192,0); glVertex3d(+0.9,-0.9,+0.9); glVertex3d(-0.9,-0.9,+0.9);
      glColor3ub(255,255,0);glVertex3d(+0.9,  -1,+0.9); glVertex3d(+0.9,  -1,-0.9); glColor3ub(192,192,0); glVertex3d(+0.9,-0.9,-0.9); glVertex3d(+0.9,-0.9,+0.9);
      glColor3ub(255,255,0);glVertex3d(-0.9,  -1,+0.9); glColor3ub(192,192,0); glVertex3d(-0.9,-0.9,+0.9); glVertex3d(-0.9,-0.9,-0.9); glColor3ub(255,255,0); glVertex3d(-0.9,  -1,-0.9);
      glColor3ub(192,192,0);glVertex3d(-0.9,-0.9,-0.9); glVertex3d(-0.9,-0.9,+0.9); glVertex3d(+0.9,-0.9,+0.9); glVertex3d(+0.9,-0.9,-0.9);
      glColor3ub(255,255,0);glVertex3d(-0.9,  -1,+0.9); glVertex3d(-0.9,  -1,-0.9); glVertex3d(+0.9,  -1,-0.9); glVertex3d(+0.9,  -1,+0.9);
    glEnd();
  glEndList();

  glNewList(WALLD, GL_COMPILE);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotated(45,0,1,0);
    glBegin(GL_QUADS);
      glColor3ub(150,150,150);
      glVertex3d(-0.05,-1,-0.9); glVertex3d(-0.05,-0.9,-0.9); glVertex3d(+0.05,-0.9,-0.9); glVertex3d(+0.05,  -1,-0.9);
      glVertex3d(-0.05,-1,+0.9); glVertex3d(+0.05,  -1,+0.9); glVertex3d(+0.05,-0.9,+0.9); glVertex3d(-0.05,-0.9,+0.9);
      glColor3ub(160,160,160);
      glVertex3d(+0.05,-1,+0.9); glVertex3d(+0.05,  -1,-0.9); glVertex3d(+0.05,-0.9,-0.9); glVertex3d(+0.05,-0.9,+0.9);
      glVertex3d(-0.05,-1,+0.9); glVertex3d(-0.05,-0.9,+0.9); glVertex3d(-0.05,-0.9,-0.9); glVertex3d(-0.05,  -1,-0.9);
      glColor3ub(140,140,140);glVertex3d(-0.05,-0.9,-0.9);glColor3ub(224,224,224);glVertex3d(-0.05,-0.9,+0.9);glVertex3d(+0.05,-0.9,+0.9);glColor3ub(140,140,140);glVertex3d(+0.05,-0.9,-0.9);
    glEnd();
    glPopMatrix();
  glEndList();

  glNewList(EXIT, GL_COMPILE);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
      glColor3ub(255,0,0);glVertex3d(-0.9,  -1,-0.9); glColor3ub(192,0,0); glVertex3d(-0.9,-0.9,-0.9); glVertex3d(+0.9,-0.9,-0.9);glColor3ub(255,0,0); glVertex3d(+0.9,  -1,-0.9);
      glVertex3d(-0.9,  -1,+0.9); glVertex3d(+0.9,  -1,+0.9); glColor3ub(192,0,0); glVertex3d(+0.9,-0.9,+0.9); glVertex3d(-0.9,-0.9,+0.9);
      glColor3ub(255,0,0);glVertex3d(+0.9,  -1,+0.9); glVertex3d(+0.9,  -1,-0.9); glColor3ub(192,0,0); glVertex3d(+0.9,-0.9,-0.9); glVertex3d(+0.9,-0.9,+0.9);
      glColor3ub(255,0,0);glVertex3d(-0.9,  -1,+0.9); glColor3ub(192,0,0); glVertex3d(-0.9,-0.9,+0.9); glVertex3d(-0.9,-0.9,-0.9); glColor3ub(255,0,0); glVertex3d(-0.9,  -1,-0.9);
      glColor3ub(192,0,0);glVertex3d(-0.9,-0.9,-0.9); glVertex3d(-0.9,-0.9,+0.9); glVertex3d(+0.9,-0.9,+0.9); glVertex3d(+0.9,-0.9,-0.9);
      glColor3ub(255,0,0);glVertex3d(-0.9,  -1,+0.9); glVertex3d(-0.9,  -1,-0.9); glVertex3d(+0.9,  -1,-0.9); glVertex3d(+0.9,  -1,+0.9);
    glEnd();
  glEndList();

  glNewList(TW, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,wall);
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2d(0,0);glVertex3i(-1,-1,-1); glTexCoord2d(0,2);glVertex3i(-1,+3,-1);
      glTexCoord2d(1,0);glVertex3i(+1,-1,-1); glTexCoord2d(1,2);glVertex3i(+1,+3,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2d(1,0);glVertex3i(-1,-1,+1); glTexCoord2d(0,0);glVertex3i(+1,-1,+1);
      glTexCoord2d(1,2);glVertex3i(-1,+3,+1); glTexCoord2d(0,2);glVertex3i(+1,+3,+1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2d(1,0);glVertex3i(+1,-1,+1); glTexCoord2d(0,0);glVertex3i(+1,-1,-1);
      glTexCoord2d(1,2);glVertex3i(+1,+3,+1); glTexCoord2d(0,2);glVertex3i(+1,+3,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2d(0,0);glVertex3i(-1,-1,+1); glTexCoord2d(0,2);glVertex3i(-1,+3,+1);
      glTexCoord2d(1,0);glVertex3i(-1,-1,-1); glTexCoord2d(1,2);glVertex3i(-1,+3,-1);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2d(0,0);glVertex3i(-1,+3,-1); glTexCoord2d(1,0);glVertex3i(-1,+3,+1);
      glTexCoord2d(0,2);glVertex3i(+1,+3,-1); glTexCoord2d(1,2);glVertex3i(+1,+3,+1);
    glEnd();
  glEndList();

  glNewList(GR, GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,gr);
    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);
    for (x = -0.8;x<=0.8;x+=0.4)
    { glTexCoord2d(x-0.1,-1);glVertex3d(x-0.1,+1,-1); glTexCoord2d(x-0.1,+1);glVertex3d(x-0.1,+1,+1);
      glTexCoord2d(x+0.1,+1);glVertex3d(x+0.1,+1,+1); glTexCoord2d(x+0.1,-1);glVertex3d(x+0.1,+1,-1);
    }
    for (x = -0.8;x<=0.8;x+=0.4)
    { glTexCoord2d(-1,x-0.1);glVertex3d(-1,+1,x-0.1); glTexCoord2d(-1,x+0.1);glVertex3d(-1,+1,x+0.1);
      glTexCoord2d(+1,x+0.1);glVertex3d(+1,+1,x+0.1); glTexCoord2d(+1,x-0.1);glVertex3d(+1,+1,x-0.1);
    }
    glEnd();
    glEnable(GL_CULL_FACE);
  glEndList();
}
#define fpx 0.00390625
#define fpy 0.0078125
void PDigit(double x,double y,byte dig,byte r, byte g,byte b,float s)
{ glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,font);
  glDisable(GL_DEPTH_TEST);
  glBegin(GL_QUADS);
  glColor3ub(r,g,b);
  glTexCoord2d((dig  )*0.0625    ,0.75+fpy);glVertex3d(x-s,y  ,-0.51);
  glTexCoord2d((dig+1)*0.0625-fpx,0.75+fpy);glVertex3d(x  ,y  ,-0.51);
  glTexCoord2d((dig+1)*0.0625-fpx,0.875   );glVertex3d(x  ,y+s,-0.51);
  glTexCoord2d((dig  )*0.0625    ,0.875   );glVertex3d(x-s,y+s,-0.51);
  glEnd();
  glEnable(GL_DEPTH_TEST);
}

void drawScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();

    if (!health) {glRotated(90,0,0,1);}
    glRotated(yr,1,0,0);
    glRotated(xr,0,1,0);
    glTranslated(xc, health==0?0.8-zc:(-zc), yc);

    RenderLevel();

    glPopMatrix();
    // HUD
    if (!health)
    { glDisable(GL_TEXTURE_2D); glDisable(GL_DEPTH_TEST);
      glBegin(GL_QUADS);glColor4ub(255,0,0,160);glVertex3d(-2,-2,-0.051);glVertex3d(2,-2,-0.051);glVertex3d(2,2,-0.051);glVertex3d(-2,2,-0.051);glEnd();
      glEnable(GL_DEPTH_TEST);
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,hudh);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glTexCoord2s(0,0);glVertex3d(-0.22,-0.2 ,-0.51);
    glTexCoord2s(1,0);glVertex3d(-0.2 ,-0.2 ,-0.51);
    glTexCoord2s(1,1);glVertex3d(-0.2 ,-0.18,-0.51);
    glTexCoord2s(0,1);glVertex3d(-0.22,-0.18,-0.51);
    glEnd();
    glEnable(GL_DEPTH_TEST);
int fps=0;
if ((t2-t1)>0){fps = 1000/(t2-t1);}
    if (health>=100)PDigit(-0.16,-0.2,health/100  ,0,255,0,0.02f);
    if (health>=10) PDigit(-0.14,-0.2,health/10%10,health<70?255:0,health<30?0:255,0,0.02f);
                    PDigit(-0.12,-0.2,health%10   ,health<70?255:0,health<30?0:255,0,0.02f);
    if (fps>=100)PDigit(-0.26,0.19,fps/100  ,255,255,255,0.01f);
    if (fps>=10) PDigit(-0.25,0.19,fps/10%10,255,255,255,0.01f);
                 PDigit(-0.24,0.19,fps%10   ,255,255,255,0.01f);
    if (jet)
    { glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,jetpack);
      glDisable(GL_DEPTH_TEST);
      glBegin(GL_QUADS);
      glColor3ub(255,255,255);
      glTexCoord2s(0,0);glVertex3d(0.21,-0.2 ,-0.51);
      glTexCoord2s(1,0);glVertex3d(0.26,-0.2 ,-0.51);
      glTexCoord2s(1,1);glVertex3d(0.26,-0.15,-0.51);
      glTexCoord2s(0,1);glVertex3d(0.21,-0.15,-0.51);
      glEnd();
      glEnable(GL_DEPTH_TEST);
    }
    if (ta)
    { glDisable(GL_TEXTURE_2D); glDisable(GL_DEPTH_TEST);
      glBegin(GL_QUADS);glColor4ub(tr,tg,tb,ta);glVertex3d(-2,-2,-0.051);glVertex3d(2,-2,-0.051);glVertex3d(2,2,-0.051);glVertex3d(-2,2,-0.051);glEnd();
      glEnable(GL_DEPTH_TEST);
    }
    if (wlds_s)
    { glDisable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glPushMatrix();
      glTranslated(0.25,-0.6+(wlds_s<16?min(wlds_s,10):((15-wlds_s)+10)-1)*0.105,-1.5);
      glRotated(wlds_s>11?100+((wlds_s-11)*8):100,0,1,0.2);
      glCallList(WALLD);
      glPopMatrix();
      glEnable(GL_DEPTH_TEST);
    }
    glFlush();
    swapBuffers();
}
char keybuf[256];
char ms[6];
static void process_events( void )
{
  SDL_Event event;
  while( SDL_PollEvent( &event ) )
    switch( event.type )
    { case SDL_KEYDOWN:        if (event.key.keysym.scancode < 256) keybuf[event.key.keysym.scancode]=1;break;
      case SDL_KEYUP:          if (event.key.keysym.scancode < 256) keybuf[event.key.keysym.scancode]=0;break;
      case SDL_MOUSEBUTTONDOWN:if (event.button.button < 6) ms[event.button.button]=1;break;
      case SDL_MOUSEBUTTONUP:  if (event.button.button < 6) ms[event.button.button]=0;break;
      case SDL_QUIT:           SDL_Quit();exit(0);break;
      case SDL_MOUSEMOTION: {
        xr+=(float)event.motion.xrel/4;
        yr+=(float)event.motion.yrel/8;
      }
    }
  while (xr<-180) xr += 360;
  while (xr> 180) xr -= 360;
  if (yr<-90) yr = -90;
  if (yr> 90) yr = 90;
}
void Control()
{
    float spd;
    t1 = t2;
    t2 = SDL_GetTicks();
    ti += t2-t1;
    while (ti < Interval) {
        t1 = t2;
        SDL_Delay(Interval - ti);
        t2 = SDL_GetTicks();
        ti += t2-t1;
    }
    for (;ti>=Interval;ti-=Interval)
    {
        process_events();
        xri=sin(-xr*deg);yri=cos(-xr*deg);
        if (zc<=FloorZ+0.1){spd=0.05f;}else{if(jet){spd=0.004f;}else{spd=0.0005f;}}
        if (health)
        {
            if (KeyPressed(SDL_SCANCODE_A)){xi+=(float)yri*spd;yi-=(float)xri*spd;}
            if (KeyPressed(SDL_SCANCODE_D)){xi-=(float)yri*spd;yi+=(float)xri*spd;}
            if (KeyPressed(SDL_SCANCODE_W)||MidMouse){xi+=(float)xri*spd;yi+=(float)yri*spd;}
            if (KeyPressed(SDL_SCANCODE_S)){xi-=(float)xri*spd;yi-=(float)yri*spd;}
            if (KeyPressed(SDL_SCANCODE_SPACE)||RightMouse) {if (zc <= FloorZ) zi = 0.075F;}
            if (jet&&(KeyPressed(SDL_SCANCODE_Q)||LLMouse)) {zi += 0.0055F;}
            if (LeftMouse&&wlds_s == 11) wlds_s++;
        }
        if (KeyPressed(SDL_SCANCODE_ESCAPE)) quit(0);
        if(MouseClick&&(!health)){LoadLevel(mapname);xc=2;yc=2;xi=0;yi=0;zi=0; health=100;FloorZ=0;jet=0;}
        xc += xi;yc += yi; zc += zi;
        ControlLevel();
//#ifdef _DEBUG
//        jet=true;
//#endif
        if (zc>FloorZ) zi -= (float)0.005;
        if (zc<FloorZ){if(zi>=-0.2f){zc=FloorZ+zi;zi=0;}else{zi=-zi/2;health-=min(health,int((zi*15)*(zi*15)*(zi*15)));tr=255;tg=0;tb=0;ta=min(255,(int)((zi*30)*(zi*30)*(zi*30)));}}
        if (zc<=(FloorZ+0.1f)){xi*=0.75F;yi*=0.75F;}else{xi*=0.995F;yi*=0.995F;zi*=0.995F;}
        if (zc>CeilZ){zc=CeilZ;zi=0;}
      }
      if (KeyPressed(SDL_SCANCODE_J)) if (health) health--;
}

void quit(int code)
{
  SDL_Quit();
  exit(code);
}

int main( int argc, char* argv[] )
{
    initGL();
    if (!LoadTextures())
        quit(1);
    createObjects();
    LoadLevel(mapname);
    t2=SDL_GetTicks();
    while( 1 ) {
        Control();
        drawScene();
    }
    return 0;
}

#ifndef INPUT_H
#define INPUT_H
#ifdef WIN32
#define DIRECTINPUT_VERSION 0x0300
#include <dinput.h>

extern DIMOUSESTATE ms;
extern LPDIRECTINPUT input;
extern LPDIRECTINPUTDEVICE keyboard;
extern LPDIRECTINPUTDEVICE mouse;
extern HANDLE KMEvent[2];
void InitDInput(HINSTANCE Instance);
static void process_events();
#endif
extern int x;
extern int y;
extern char keybuf[512];

#define GetKeyboardState() keyboard->GetDeviceState(sizeof(keybuf),(LPVOID)&keybuf)
#define Accellerate(x) {} //x = sqrt(abs(x))*x;
#define GetMouseState() mouse->GetDeviceState(sizeof(ms),(LPVOID)&ms);Accellerate(ms.lX); Accellerate(ms.lY); x += ms.lX;y = max(-90,min(90,y+ms.lY));
#define KeyPressed(key) (keybuf[key])
#define mr(x1,y1,x2,y2) ((x>=(x1))&&(y>=(y1))&&(x<=(x2))&&(y<=(y2)))
extern char ms[5];
#define LeftMouse (ms[0])
#define MidMouse (ms[1])
#define RightMouse (ms[2])
#define LLMouse (ms[3])
#define RRMouse (ms[4])
#define MouseClick (ms[4]||ms[0]||ms[1]||ms[2]||ms[3])
#endif

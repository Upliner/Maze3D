// Keyboard/Mouse functions
#include "input.h"
#include "Common.h"
#include <SDL/SDL.h>
int x = 0;
int y = 0;
char keybuf[512];
char ms[5];
#ifdef WIN32
DIMOUSESTATE ms;
LPDIRECTINPUT input;
LPDIRECTINPUTDEVICE keyboard;
LPDIRECTINPUTDEVICE mouse;
HANDLE KMEvent[2];
void InitDInput(HINSTANCE Instance)
{
  if FAILED(DirectInputCreate(Instance,DIRECTINPUT_VERSION,(IDirectInput**)&input, NULL))exit(-1);

  if FAILED(input->CreateDevice(GUID_SysKeyboard,(IDirectInputDevice**)&keyboard, NULL))exit(-1);
  if FAILED(input->CreateDevice(GUID_SysMouse   ,(IDirectInputDevice**)&mouse   , NULL))exit(-1);
  keyboard->SetDataFormat(&c_dfDIKeyboard);
  mouse->   SetDataFormat(&c_dfDIMouse);
  keyboard->SetCooperativeLevel(Window,DISCL_BACKGROUND|DISCL_NONEXCLUSIVE);
  mouse->   SetCooperativeLevel(Window,DISCL_BACKGROUND|DISCL_NONEXCLUSIVE);
  keyboard->SetEventNotification(&KMEvent[0]);
  mouse->   SetEventNotification(&KMEvent[1]);
  keyboard->Acquire();
  mouse->   Acquire();
}
#else
static void process_events( void )
{
    /* Our SDL event placeholder. */
    SDL_Event event;

    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {
//SDL_PollEvent( &event );
        switch( event.type ) {
        case SDL_KEYDOWN:
            /* Handle key presses. */
keybuf[event.key.keysym.sym]=1;
  //          handle_key_down( &event.key.keysym );
            break;
        case SDL_KEYUP:
            /* Handle key presses. */
keybuf[event.key.keysym.sym]=0;
  //          handle_key_down( &event.key.keysym );
            break;
        case SDL_MOUSEBUTTONDOWN:
            /* Handle key presses. */
ms[event.button.button]=1;
  //          handle_key_down( &event.key.keysym );
            break;
        case SDL_MOUSEBUTTONUP:
            /* Handle key presses. */
ms[event.button.button]=0;
  //          handle_key_down( &event.key.keysym );
            break;
        case SDL_QUIT:
            /* Handle quit requests (like Ctrl-c). */
            quit( 0 );
            break;
        }
    }
int x1,y1;
SDL_GetMouseState(&x1,&y1);
SDL_WarpMouse(w/2,h/2);
x+=x1-(w/2);y+=y1-(h/2);
}
#endif

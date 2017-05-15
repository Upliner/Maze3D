// Keyboard/Mouse functions
#include "input.h"
#include "Common.h"
#include <SDL/SDL.h>
int x = 0;
int y = 0;
char keybuf[512];
char ms[5];
static void process_events( void )
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
        case SDL_KEYDOWN:
            keybuf[event.key.keysym.sym]=1;
            break;
        case SDL_KEYUP:
            keybuf[event.key.keysym.sym]=0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            ms[event.button.button]=1;
            break;
        case SDL_MOUSEBUTTONUP:
            ms[event.button.button]=0;
            break;
        case SDL_QUIT:
            quit( 0 );
            break;
        }
    }
    int x1,y1;
    SDL_GetMouseState(&x1,&y1);
    SDL_WarpMouse(w/2,h/2);
    x+=x1-(w/2);y+=y1-(h/2);
}

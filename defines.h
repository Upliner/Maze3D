#ifndef DEFINES_H
#define DEFINES_H

//#include <sys/types.h>

//#define a PeekMessage(&msg, 0, 0, 0, PM_REMOVE);TranslateMessage(&msg);DispatchMessage(&msg);

//#define wa MsgWaitForMultipleObjects(2,KMEvent,TRUE,INFINITE,QS_ALLEVENTS); PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);TranslateMessage(&msg);DispatchMessage(&msg);
//#define ka MsgWaitForMultipleObjects(1,&KMEvent[0],TRUE,INFINITE,QS_ALLEVENTS); PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);TranslateMessage(&msg);DispatchMessage(&msg);
//#define ma MsgWaitForMultipleObjects(1,&KMEvent[1],TRUE,INFINITE,QS_ALLEVENTS); PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);TranslateMessage(&msg);DispatchMessage(&msg);


#define PI 3.1415926535897932384626433832795
#define deg (PI/180)

#define BOX 1
#define FLOOR 2
#define EXTWALL 3
#define JETPACK 4
#define TRAP 5
#define BUTTON 6
#define DOOR 7
#define KEY 8
#define TELEPORTER 9
#define ONEPASS 10
#define WALLD 11
#define EXIT 12
#define TW 13
#define GR 14
#define BOX_OPTIM_CEILONLY 32
//#define TW_OPTIM_BOX 14
#define LEVELS 64

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef byte BYTE;
typedef word WORD;
typedef dword DWORD;
typedef long LONG;
#define FALSE false
#define ZeroMemory(mem,len) memset(mem,0,len)
#endif

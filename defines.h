#ifndef DEFINES_H
#define DEFINES_H
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
#define LEVELS 64

inline double max(double a, double b) {
    if (a>b) return a; else return b;
}
inline double min(double a, double b) {
    if (a>b) return b; else return a;
}

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

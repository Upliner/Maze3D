#ifndef INPUT_H
#define INPUT_H
#define KeyPressed(key) (keybuf[key])
#define mr(x1,y1,x2,y2) ((x>=(x1))&&(y>=(y1))&&(x<=(x2))&&(y<=(y2)))
#define LeftMouse (ms[1])
#define MidMouse (ms[2])
#define RightMouse (ms[3])
#define LLMouse (ms[4])
#define RRMouse (ms[5])
#define MouseClick (ms[5]||ms[4]||ms[0]||ms[1]||ms[2]||ms[3])
#endif

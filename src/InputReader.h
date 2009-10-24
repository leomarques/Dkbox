#ifndef INPUTREADER_H_INCLUDED
#define INPUTREADER_H_INCLUDED

#define MOUSE1 -1
#define MOUSE2 -2
#define TAB 11
#define NOINPUT -10
#define QUIT -11

#include <Allegro.h>

extern int mouseLock;

int readInput(void);
void freeAllInput(void);

#endif // INPUTREADER_H_INCLUDED

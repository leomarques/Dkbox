#ifndef INPUTREADER_H_INCLUDED
#define INPUTREADER_H_INCLUDED

#define NKEYS 13
#define MOUSE1 10
#define MOUSE2 11
#define KEYD 12

#define NOINPUT -10
#define QUIT -11
#define KEYTAB -12

#include <Allegro.h>

extern int mouseLock;

int readInput(void);
void freeAllInput(void);

#endif // INPUTREADER_H_INCLUDED

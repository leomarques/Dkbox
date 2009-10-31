#ifndef ENGICK_H_INCLUDED
#define ENGICK_H_INCLUDED

#include "Game.h"

#define DEFAULTRESX 800
#define DEFAULTRESY 600
#define DEFAULTCOLORDEPTH 32
#define FPS 60

void engickStart(void);
void init(void);
void playGame(void);
void abortOnError(void);
void timer(void);
void closeButtonHandler(void);

#endif // ENGICK_H_INCLUDED

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#define DEFAULTRESX 800
#define DEFAULTRESY 600
#define DEFAULTCOLORDEPTH 32
#define FPS 60
#define WINTITLE "Dickbox"

#include <allegro.h>
#include <time.h>

#include "Game.h"
#include "Input.h"

extern BITMAP *buffer;
extern volatile int counter;

void startEngine(void);
void init(void);
void playGame(void);
void abortOnError(void);
void closeButtonHandler(void);
void timer(void);

#endif // ENGINE_H_INCLUDED

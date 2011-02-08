#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Stage.h"
#include "DebugDraw.h"

#define WINTITLE "Dickbox - r21"

extern DebugDraw *debugDraw;
extern int gtime;

void gameInit(void);
bool gameStep(void);
BITMAP* gameRender(void);
void gameEnd(void);

#endif // GAME_H_INCLUDED

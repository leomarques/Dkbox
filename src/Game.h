#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameUtils.h"
#include "BodyManager.h"
#include "InputReader.h"
#include "DebugDraw.h"

#include <time.h>

void gameInit(void);
bool gameStep(void);
void gameRender(int counter1);
void gameEnd(void);

#endif // GAME_H_INCLUDED

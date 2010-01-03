#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <Allegro.h>
#include "Stage.h"

void gameInit(void);
bool gameStep(void);
void gameRender(void);
void gameEnd(void);

#endif // GAME_H_INCLUDED

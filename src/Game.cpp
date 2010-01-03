#include "Game.h"

Stage *stage;

void gameInit(void)
{
    stage = new Stage();
}

bool gameStep(void)
{
    return stage->step();
}

void gameRender(void)
{
    stage->render();
}

void gameEnd(void)
{
    delete stage;
    destroy_bitmap(buffer);
}

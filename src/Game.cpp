#include "Game.h"

Stage *stage;
BITMAP *bmp;
DebugDraw *debugDraw;
int gtime;

void gameInit(void)
{
    bmp = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(bmp);
    gtime = 0;
    debugDraw = new DebugDraw(bmp);
    stage = new Stage();
}

bool gameStep(void)
{
    return stage->step();
    gtime++;
}

BITMAP* gameRender(void)
{
    stage->render(bmp);
    return bmp;
}

void gameEnd(void)
{
    delete stage;
    delete debugDraw;
    destroy_bitmap(bmp);
}

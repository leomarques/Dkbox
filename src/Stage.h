#ifndef STAGE_H
#define STAGE_H

#include <allegro.h>
#include <Box2D.h>

#include "World.h"
#include "DebugDraw.h"
#include "FreeDraw.h"
#include "CustomBox.h"
#include "CustomCircle.h"
#include "CustomPolygon.h"
#include "GameUtils.h"
#include "MathUtils.h"
#include "Input.h"
#include "Game.h"

#define RANDHALFSIZE (RANDOM(6, 35)) / 100.0f
#define RANDBODYSIZE b2Vec2(RANDHALFSIZE, RANDHALFSIZE)
#define SMALLHALFSIZE (6 / 100.0f)
#define SMALLBODYSIZE b2Vec2(SMALLHALFSIZE, SMALLHALFSIZE)

class Stage
{
public:
    Stage();
    ~Stage();
    bool step(void);
    void render(BITMAP *buffer);

private:
    World *world;
    FreeDraw *freeDraw;
    CustomBox *customBox;
    CustomCircle *customCircle;
    CustomPolygon *customPolygon;
    bool menuOn, debugDrawOn, bmpDrawOn, cleanModeOn, autoDumpOn, cursorOn, smallBodiesOn;
    b2Vec2 bodiesSize;
    float32 bodiesRadius;
    b2Vec2 gravity;
    volatile int dt;

    enum BodyType { Random, Box, Circle, Free_Draw, Custom_Box, Custom_Circle, Custom_Polygon };

    BodyType bodyType;

    void toggleDebugDraw(void);
    void createGround(void);
    void pyramidShow(void);
};

#endif // STAGE_H

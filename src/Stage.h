#ifndef STAGE_H
#define STAGE_H

#include <Allegro.h>
#include <Box2D.h>

#include "World.h"
#include "DebugDraw.h"
#include "FreeDraw.h"
#include "GameUtils.h"
#include "MathUtils.h"
#include "Input.h"
#include "Engine.h"

#define RANDBODYSIZE (RANDOM(6, 35)) / 100.0f

class Stage
{
public:
    Stage();
    ~Stage();
    bool step(void);
    void render(void);

private:
    World *world;
    DebugDraw *debugDraw;
    FreeDraw *freeDraw;
    bool menuOn, debugDrawOn, bmpDrawOn;
    volatile int dt;

    enum BodyType { Random, Box, Circle, _FreeDraw };

    BodyType bodyType;

    void toggleDebugDraw(void);
    void createGround(void);
    void pyramidShow(void);
};

#endif // STAGE_H

#ifndef STAGE_H
#define STAGE_H

#include <Allegro.h>
#include "World.h"
#include "GameUtils.h"
#include "Input.h"
#include "Engine.h"

class World;

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
    bool menuOn, debugDrawOn, bmpDrawOn;
    volatile int dt;

    enum BodyType { Random, Box, Circle };

    BodyType bodyType;

    void createGround(void);
    void pyramidShow(void);
};

#endif // STAGE_H

#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <Box2D.h>
#include <Allegro.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#include "DebugDraw.h"
#include "Body.h"
#include "Bomb.h"

class DebugDraw;

#define TIMESTEP 1.0f / 60.0f
#define ITERATIONS 10

#define DENSITY 1.0f
#define FRICTION 0.3f
#define ANGULARDAMPING 0.8f
#define BOXRESTITUTION 0.23f
#define CIRCRESTITUTION 0.5f
#define BOMBRADIUS 0.087f
#define MAXBODIES 500

class World
{
public:
    vector<Body*> bodyList;
    bool simulateOn, staticModeOn;

    World(void);
    ~World(void);

    void simulate(void);
    void toggleDebugDraw(void);
    void toggleSimulation(void);
    void toggleStaticMode(void);

    bool makeBox(const b2Vec2 coordinates, const b2Vec2 dimensions);
    bool makeCircle(const b2Vec2 coordinates, const float32 radius);
    bool makeBomb(const b2Vec2 coordinates);

    void destroyBody(Body *body);
    void destroyLastBody(void);
    void destroyAllBodies(void);

private:
    b2World *world;
    DebugDraw *debugDraw;
    bool debugDrawOn;

    void afterStepChecks(void);
};

class BoundaryListener : public b2BoundaryListener
{
    void Violation(b2Body* body)
    {
        ((Body*) (body->GetUserData()))->markedForDeletion = true;
    }
};

#endif // WORLD_H_INCLUDED

#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <Box2D.h>
#include <allegro.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#include "RenderUtils.h"
#include "GameUtils.h"
#include "MathUtils.h"
#include "DebugDraw.h"
#include "Body.h"
#include "Bomb.h"

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
    void setDebugDraw(DebugDraw *debugDraw);
    void toggleSimulation(void);
    void toggleStaticMode(void);

    Body* makeBox(const b2Vec2 coordinates, const b2Vec2 dimensions);
    Body* makeCircle(const b2Vec2 coordinates, const float32 radius);
    Body* makeBomb(const b2Vec2 coordinates);
    Body* makeBody(vector<Point> points);

    void wakeUpAllBodies(void);
    void setGravity(b2Vec2 gravity);

    void destroyBody(Body *body);
    void destroyLastBody(void);
    void destroyLastNonStaticBody(void);
    void destroyAllBodies(void);
    void destroyAllNonStaticBodies(void);

private:
    b2World *world;

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

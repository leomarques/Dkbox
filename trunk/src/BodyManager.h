#ifndef BODYMANAGER_H_INCLUDED
#define BODYMANAGER_H_INCLUDED

#include <vector>
#include <queue>
#include <time.h>

#include "GameUtils.h"
#include "Bomb.h"
#include "InputReader.h"
#include "MathUtils.h"

#define RANDBODYSIZE (RANDOM(6, 35)) / 100.0f
#define FRICTION 0.3f
#define DENSITY 1.0f
#define ANGULARDAMPING 0.7f
#define BOXRESTITUTION 0.23f
#define CIRCRESTITUTION 0.5f
#define BOMBRADIUS 0.087f
#define MAXBODIES 500
#define MINPOINTDISTANCE 20

using namespace std;

extern queue<b2Body *> OOBBodies;

class BodyManager
{
    b2World *bmWorld;
    vector<Bomb *> bombs;

    void makeBody(const b2Vec2 coordinates, const int mouseButton);
    void createBody(const b2Vec2 coordinates, const b2Vec2 dimensions);
    void createBody(const b2Vec2 coordinates, const float32 radius);
    void createBody(const b2Vec2 coordinates);
    void createBody(void);
    BITMAP* createBodyBitmap(const b2Vec2 dimensions);
    BITMAP* createBodyBitmap(const float32 radius, const int color);
    void createGround(void);
    void pyramidShow(void);
    void customBoxMode(void);
    void freeDrawMode(void);
    void destroyBody(b2Body *body);
    void destroyLastBody(void);
    void destroyAllBodies(void);
    void reset(void);

public:
    int bodyType, staticMode;
    bool customModeOn, freeDrawModeOn;
    int cusX1, cusX2, cusY1, cusY2;
    vector<Point> freeDrawPoints;

    BodyManager(b2World *world);
    ~BodyManager(void);
    void getInput(const int in);
    void checkBombs(void);
    void destroyOOBBodies(void);
    void checkCustomBox(void);
    void checkFreeDraw(void);

    inline int GetBombCount(void)
    {
        return bombs.size();
    }
};

class BoundaryListener : public b2BoundaryListener
{
    void Violation(b2Body* body)
    {
        OOBBodies.push(body);
    }
};

#endif // BODYMANAGER_H_INCLUDED

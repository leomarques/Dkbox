#include "World.h"

World::World(void)
{
    b2AABB worldAABB;
    worldAABB.lowerBound.Set(-40.0f, -20.0f);
    worldAABB.upperBound.Set(40.0f, 100.0f);

    world = new b2World(worldAABB, b2Vec2(0.0f, -10.0f), true);

    world->SetBoundaryListener(new BoundaryListener());

    staticModeOn = false;
    simulateOn = true;
}

World::~World(void)
{
    destroyAllBodies();
    delete world;
}

void World::simulate(void)
{
    if (!simulateOn)
        return;

    world->Step(TIMESTEP, ITERATIONS);
    afterStepChecks();
}

void World::setDebugDraw(DebugDraw *debugDraw)
{
    world->SetDebugDraw(debugDraw);
}

void World::toggleStaticMode(void)
{
    staticModeOn = !staticModeOn;
}

void World::toggleSimulation(void)
{
    simulateOn = !simulateOn;
}

bool World::makeBox(const b2Vec2 coordinates, const b2Vec2 dimensions)
{
    if (world->GetBodyCount() > MAXBODIES) return false;

    b2BodyDef bodyDef;
    bodyDef.position.Set(coordinates.x, coordinates.y);
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonDef shapeDef;
    shapeDef.SetAsBox(dimensions.x, dimensions.y);
    if (!staticModeOn) shapeDef.density = DENSITY;
    shapeDef.friction = FRICTION;
    shapeDef.restitution = BOXRESTITUTION;

    body->CreateShape(&shapeDef);
    body->SetMassFromShapes();

    Body *b = new Body(body, createBoxBitmap(dimensions));
    if (!b->bmp)
    {
        delete b;
        return false;
    }

    bodyList.push_back(b);

    return true;
}

bool World::makeCircle(const b2Vec2 coordinates, const float32 radius)
{
    if (world->GetBodyCount() > MAXBODIES) return false;

    b2BodyDef bodyDef;
    bodyDef.angularDamping = ANGULARDAMPING;
    bodyDef.position.Set(coordinates.x, coordinates.y);
    b2Body* body = world->CreateBody(&bodyDef);

    b2CircleDef shapeDef;
    shapeDef.radius = radius;
    if (!staticModeOn) shapeDef.density = DENSITY;
    shapeDef.friction = FRICTION;
    shapeDef.restitution = CIRCRESTITUTION;

    body->CreateShape(&shapeDef);
    body->SetMassFromShapes();

    Body *b = new Body(body, createCircleBitmap(radius, GREEN));
    if (!b->bmp)
    {
        delete b;
        return false;
    }

    bodyList.push_back(b);

    return true;
}

bool World::makeBomb(const b2Vec2 coordinates)
{
    if (world->GetBodyCount() > MAXBODIES) return false;

    b2BodyDef bodyDef;
    bodyDef.angularDamping = ANGULARDAMPING;
    bodyDef.position.Set(coordinates.x, coordinates.y);
    b2Body* body = world->CreateBody(&bodyDef);

    b2CircleDef shapeDef;
    shapeDef.radius = BOMBRADIUS;
    if (!staticModeOn) shapeDef.density = DENSITY;
    shapeDef.friction = FRICTION;
    shapeDef.restitution = CIRCRESTITUTION;

    body->CreateShape(&shapeDef);
    body->SetMassFromShapes();

    Bomb *b = new Bomb(body, createCircleBitmap(BOMBRADIUS, RED));
    if (!b->bmp)
    {
        delete b;
        return false;
    }

    bodyList.push_back(b);

    return true;
}

Body* World::makeBody(vector<Point> points)
{
    if (world->GetBodyCount() > MAXBODIES || (int) points.size() < 3) return NULL;

    b2BodyDef bodyDef;
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonDef shapeDef;
    if (!staticModeOn) shapeDef.density = DENSITY;
    shapeDef.friction = FRICTION;
    shapeDef.restitution = BOXRESTITUTION;

    float32 x[1 << 9], y[1 << 9];
    for (int i = 0; i < (int) points.size(); i++)
    {
        x[i] = coordXAllegToB2(points[i].x);
        y[i] = coordYAllegToB2(points[i].y);
    }

    b2Polygon pgon(x, y, (int) points.size());

    DecomposeConvexAndAddTo(&pgon, body, &shapeDef);

    body->SetMassFromShapes();

    Body *b = new Body(body);
    bodyList.push_back(b);

    return b;
}

void World::destroyBody(Body *body)
{
    vector<Body*>::iterator it = find(bodyList.begin(), bodyList.end(), body);
    delete *it;
    bodyList.erase(it);
}

void World::destroyLastBody(void)
{
    if (!bodyList.empty()) destroyBody(bodyList.back());
}

void World::destroyAllBodies(void)
{
    while (!bodyList.empty())
    {
        destroyLastBody();
    }
}

void World::afterStepChecks(void)
{
    queue<Body*> purgatory;
    for (vector<Body*>::iterator it = bodyList.begin(); it != bodyList.end(); ++it)
    {
        if ((*it)->isBomb) ((Bomb*) (*it))->checkFuse();
        if ((*it)->markedForDeletion) purgatory.push(*it);
    }

    while (!purgatory.empty())
    {
        destroyBody(purgatory.front());
        purgatory.pop();
    }
}

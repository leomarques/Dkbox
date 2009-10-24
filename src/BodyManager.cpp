#include "BodyManager.h"

queue<b2Body *> OOBBodies;

BodyManager::BodyManager(b2World *world)
{
    bmWorld = world;
    bodyType = 1;
    customModeOn = false;
    staticMode = -1;

    createGround();
    createBody(coordAllegToB2(SCREEN_W / 2, SCREEN_H / 2), b2Vec2(0.4f, 0.4f));
}

BodyManager::~BodyManager(void)
{
    destroyAllBodies();
}

void BodyManager::getInput(const int in)
{
    switch (in)
    {
    case -1:
    case -2:
        makeBody(coordAllegToB2(mouse_x, mouse_y), in);
        break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        bodyType = in;
        break;

    case 6:
        destroyLastBody();
        break;

    case 7:
        staticMode *= -1;
        break;

    case 0:
        reset();
        break;

    default:
        break;
    }
}

void BodyManager::makeBody(const b2Vec2 coordinates, const int mouseButton)
{
    if (bmWorld->GetBodyCount() > 500) return;

    if (mouseButton == -2)
    {
        createBody(coordinates);
        return;
    }

    switch (bodyType)
    {
    case 1:
        switch (rand() % 2)
        {
        case 0:
            createBody(coordinates, b2Vec2(RANDBODYSIZE, RANDBODYSIZE));
            break;

        case 1:
            createBody(coordinates, RANDBODYSIZE);
            break;

        default:
            break;
        }
        break;

    case 2:
        createBody(coordinates, b2Vec2(RANDBODYSIZE, RANDBODYSIZE));
        break;

    case 3:
        createBody(coordinates, RANDBODYSIZE);
        break;

    case 4:
        createBody(coordinates);
        break;

    case 5:
        customMode();
        break;

    default:
        break;
    }
}

// Creates boxes.
void BodyManager::createBody(const b2Vec2 coordinates, const b2Vec2 dimensions)
{
    // Creating body and adding it to the world.
    b2BodyDef bodyDef;
    bodyDef.position.Set(coordinates.x, coordinates.y);
    b2Body* body = bmWorld->CreateBody(&bodyDef);

    // Defining shape and adding it to the body.
    b2PolygonDef shapeDef;
    shapeDef.SetAsBox(dimensions.x, dimensions.y);
    if (staticMode == -1) shapeDef.density = DENSITY;
    shapeDef.friction = FRICTION;
    shapeDef.restitution = BOXRESTITUTION;

    body->CreateShape(&shapeDef);
    body->SetMassFromShapes();
    body->SetUserData(createBodyBitmap(dimensions));
    if (!body->GetUserData()) bmWorld->DestroyBody(body);
}

// Creates circles.
void BodyManager::createBody(const b2Vec2 coordinates, const float32 radius)
{
    // Creating body and adding it to the world.
    b2BodyDef bodyDef;
    // Angular damping is required for circles to stop rolling.
    bodyDef.angularDamping = ANGULARDAMPING;
    bodyDef.position.Set(coordinates.x, coordinates.y);
    b2Body* body = bmWorld->CreateBody(&bodyDef);

    // Defining shape and adding it to the body.
    b2CircleDef shapeDef;
    shapeDef.radius = radius;
    if (staticMode == -1) shapeDef.density = DENSITY;
    shapeDef.friction = FRICTION;
    shapeDef.restitution = CIRCRESTITUTION;

    body->CreateShape(&shapeDef);
    body->SetMassFromShapes();
    body->SetUserData(createBodyBitmap(radius, GREEN));
    if (!body->GetUserData()) bmWorld->DestroyBody(body);
}

// Creates bombs.
void BodyManager::createBody(const b2Vec2 coordinates)
{
    b2BodyDef bodyDef;
    // Angular damping is required for circles to stop rolling.
    bodyDef.angularDamping = ANGULARDAMPING;
    bodyDef.position.Set(coordinates.x, coordinates.y);
    b2Body* body = bmWorld->CreateBody(&bodyDef);

    // Defining shape and adding it to the body.
    b2CircleDef shapeDef;
    shapeDef.radius = BOMBRADIUS;
    if (staticMode == -1) shapeDef.density = DENSITY;
    shapeDef.friction = FRICTION;
    shapeDef.restitution = CIRCRESTITUTION;

    body->CreateShape(&shapeDef);
    body->SetMassFromShapes();
    body->SetUserData(createBodyBitmap(BOMBRADIUS, RED));
    if (!body->GetUserData()) bmWorld->DestroyBody(body);

    bombs.push_back(new Bomb(body, bmWorld));
}

void BodyManager::createGround(void)
{
    int b = staticMode;
    staticMode = 1;
    createBody(coordAllegToB2(SCREEN_W / 2, SCREEN_H - 15), b2Vec2(6.0f, 0.15f));
    staticMode  = b;
}

// Creates rectangles bitmaps.
BITMAP* BodyManager::createBodyBitmap(const b2Vec2 dimensions)
{
    BITMAP* bmp = create_bitmap((int) (dimensions.x * 2 * scale), (int) (dimensions.y * 2 * scale));
    if (!bmp) return bmp;

    clear(bmp);
    rect(bmp, 0, 0, bmp->w - 1, bmp->h - 1, GREEN);

    return bmp;
}

// Creates circles bitmaps.
BITMAP* BodyManager::createBodyBitmap(const float32 radius, const int color)
{
    BITMAP* bmp = create_bitmap((int) (radius * 2 * scale) + 1, (int) (radius * 2 * scale) + 1);
    if (!bmp) return bmp;

    clear_to_color(bmp, TRANSPARENT);
    circle(bmp, (int) (radius * scale), (int) (radius * scale), (int) (radius * scale), color);
    line(bmp, bmp->w / 2, bmp->h / 2, bmp->w / 2, 0, color);

    return bmp;
}

// Updates mouse position to draw custom box.
void BodyManager::customMode(void)
{
    if (!customModeOn)
    {
        customModeOn = true;

        cusX1 = mouse_x;
        cusY1 = mouse_y;
        cusX2 = mouse_x;
        cusY2 = mouse_y;
    }
    else
    {
        cusX2 = mouse_x;
        cusY2 = mouse_y;
    }
}

void BodyManager::checkCustom(void)
{
    if (mouse_b != 1 && customModeOn)
    {
        customModeOn = false;

        b2Vec2 c1 = coordAllegToB2(cusX1, cusY1);
        b2Vec2 c2 = coordAllegToB2(cusX2, cusY2);

        float32 w = c2.x - c1.x;
        if (w < 0.0f) w = -w;

        float32 h = c2.y - c1.y;
        if (h < 0.0f) h = -h;

        if (w < 0.1f) w = 0.1f;
        if (h < 0.1f) h = 0.1f;

        createBody(b2Vec2(c1.x + (c2.x - c1.x) / 2.0f, c1.y + (c2.y - c1.y) / 2.0f), b2Vec2(w / 2.0f, h / 2.0f));
    }
}

// Checking bombs' fuses.
void BodyManager::checkBombs(void)
{
    queue<Bomb *> blownUpBombs;

    for (unsigned int i = 0; i < bombs.size(); i++)
        if (bombs[i]->checkFuse())
            blownUpBombs.push(bombs[i]);

    while (!blownUpBombs.empty())
    {
        destroyBody(blownUpBombs.front()->GetBody());
        blownUpBombs.pop();
    }
}

void BodyManager::destroyAllBodies(void)
{
    destroyOOBBodies();
    bombs.clear();

    b2Body* body = bmWorld->GetBodyList();
    for (int count = 0, bodyCount = bmWorld->GetBodyCount() - 1; count < bodyCount; count++)
    {
        b2Body *b = body;
        body = body->GetNext();

        destroyBody(b);
    }
}

void BodyManager::destroyBody(b2Body *body)
{
    // If body is a bomb, first remove it from bomb vector.
    for (vector<Bomb *>::iterator it = bombs.begin(); it != bombs.end() ; it++)
    {
        if ((*it)->GetBody() == body)
        {
            destroy_bitmap((BITMAP*) body->GetUserData());
            bmWorld->DestroyBody(body);

            delete *it;
            bombs.erase(it);
            return;
        }
    }

    destroy_bitmap((BITMAP*) body->GetUserData());
    bmWorld->DestroyBody(body);
}

void BodyManager::destroyLastBody(void)
{
    if (bmWorld->GetBodyCount() < 2) return;
    destroyBody(bmWorld->GetBodyList());
}

// Destroys bodies that go out of the world boundaries.
void BodyManager::destroyOOBBodies(void)
{
    while (!OOBBodies.empty())
    {
        destroyBody(OOBBodies.front());
        OOBBodies.pop();
    }
}

void BodyManager::reset(void)
{
    destroyAllBodies();
    createGround();
}
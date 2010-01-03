#include "Bomb.h"

Bomb::Bomb(b2Body *body, b2World *world, BITMAP *bmp) : Body(body, world, bmp)
{
    fuse = 120;
    isBomb = true;
}

Bomb::~Bomb(void)
{
    destroy_bitmap(bmp);
    world->DestroyBody(body);
}

void Bomb::checkFuse(void)
{
    if (--fuse <= 0)
    {
        blowUp();
        markedForDeletion = true;
    }
}

void Bomb::blowUp(void)
{
    int bodyCount = world->GetBodyCount() - 1;
    for (b2Body* b = world->GetBodyList(); bodyCount > 0; b = b->GetNext(), bodyCount--)
    {
        float32 dx = b->GetPosition().x - body->GetPosition().x;
        float32 dy = b->GetPosition().y - body->GetPosition().y;
        float32 dist = b2Vec2(dx, dy).Length();
        dx /= dist;
        dy /= dist;
        float32 pow = EXPLOSION / dist;
        b->ApplyImpulse(pow * b2Vec2(dx, dy), b->GetWorldCenter());
    }
}

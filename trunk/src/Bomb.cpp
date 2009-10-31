#include "Bomb.h"

Bomb::Bomb(b2Body *body, b2World *world)
{
    bBody = body;
    bWorld = world;
    fuse = 0;
}

bool Bomb::checkFuse(void)
{
    if (++fuse >= FUSETIME)
    {
        blowUp();
        return true;
    }
    return false;
}

void Bomb::blowUp(void) const
{
    // Applies an impulse on all bodies based on distance.
    int count = 0, bodyCount = bWorld->GetBodyCount() - 1;
    for (b2Body* body = bWorld->GetBodyList(); count < bodyCount; body = body->GetNext(), count++)
    {
        float32 dx = body->GetPosition().x - bBody->GetPosition().x;
        float32 dy = body->GetPosition().y - bBody->GetPosition().y;
        float32 dist = b2Vec2(dx, dy).Length();
        dx /= dist;
        dy /= dist;
        float32 pow = EXPLOSION / dist;
        body->ApplyImpulse(pow * b2Vec2(dx, dy), body->GetWorldCenter());
    }
}

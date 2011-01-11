#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <Box2D.h>
#include <Allegro.h>

#include "MathUtils.h"
#include "GameUtils.h"

class Body
{
public:
    b2Body *body;
    BITMAP *bmp;
    bool markedForDeletion, isBomb;

    Body(b2Body *_body)
    {
        body = _body;
        body->SetUserData(this);
        markedForDeletion = false;
        isBomb = false;
		bmp = 0;
    }

    Body(b2Body *_body, BITMAP *_bmp)
    {
        body = _body;
        body->SetUserData(this);
        markedForDeletion = false;
        isBomb = false;
        bmp = _bmp;
    }

    ~Body(void)
    {
        destroy_bitmap(bmp);
        getB2World()->DestroyBody(body);
    }

    b2World* getB2World(void)
    {
        return body->GetWorld();
    }

    b2Vec2 getB2Position(void)
    {
        return body->GetWorldCenter();
    }

    Point getAllegPosition(void)
    {
        return coordB2ToAlleg(getB2Position());
    }

    float32 getMass(void)
    {
        return body->GetMass();
    }

    float32 getB2Angle(void)
    {
        return body->GetAngle();
    }

    fixed getAllegAngle(void)
    {
        return angleB2ToAlleg(getB2Angle());
    }

    bool operator==(Body *b)
    {
        return body == b->body;
    }
};

#endif // BODY_H_INCLUDED

#include "DebugDraw.h"

DebugDraw::DebugDraw(BITMAP *bmp)
{
    this->bmp = bmp;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    int lx = coordXB2ToAlleg(vertices[0].x), ly = coordYB2ToAlleg(vertices[0].y), ax, ay;
    for (int32 i = 1; i < vertexCount; ++i)
    {
        ax = coordXB2ToAlleg(vertices[i].x);
        ay = coordYB2ToAlleg(vertices[i].y);

        line(bmp, lx, ly, ax, ay, BLUE);

        lx = ax;
        ly = ay;
    }

    ax = coordXB2ToAlleg(vertices[0].x);
    ay = coordYB2ToAlleg(vertices[0].y);
    line(bmp, lx, ly, ax, ay, BLUE);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    circle(bmp, coordXB2ToAlleg(center.x), coordYB2ToAlleg(center.y), (int) (radius * SCALE), BLUE);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    line(bmp, coordXB2ToAlleg(p1.x), coordYB2ToAlleg(p1.y), coordXB2ToAlleg(p2.x), coordYB2ToAlleg(p2.y), BLUE);
}

void DebugDraw::DrawXForm(const b2XForm& xf){}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){}


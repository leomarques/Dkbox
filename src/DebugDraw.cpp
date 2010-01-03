#include "DebugDraw.h"

DebugDraw::DebugDraw(void)
{
    uint32 flags = 0;
    flags += b2DebugDraw::e_shapeBit;
    flags += b2DebugDraw::e_coreShapeBit;
    SetFlags(flags);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    for (int32 i = 1; i < vertexCount; i++)
    {
        drawLine(buffer, coordB2ToAlleg(vertices[i]), coordB2ToAlleg(vertices[i - 1]), BLUE);
    }

    drawLine(buffer, coordB2ToAlleg(vertices[vertexCount - 1]), coordB2ToAlleg(vertices[0]), BLUE);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    drawCircle(buffer, coordB2ToAlleg(center), (int) (radius * SCALE), BLUE);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    drawLine(buffer, coordB2ToAlleg(p1), coordB2ToAlleg(p2), BLUE);
}

void DebugDraw::DrawXForm(const b2XForm& xf){}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){}


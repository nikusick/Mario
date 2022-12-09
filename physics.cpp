#include "physics.h"


void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    // Standard OpenGL rendering stuff
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_POLYGON);
    for (int i = 0; i < vertexCount; i++) {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

// We just need to have these to prevent override errors, they don't actually do anything right now
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
void DebugDraw::DrawTransform(const b2Transform& xf) {}

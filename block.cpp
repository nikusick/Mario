#include "block.h"

Block:: Block(qreal x, qreal y, const std::string& img, b2World* world)
{
    _pixmap = QPixmap(QString::fromStdString(TILES_PATH + img));
    setPos(x, y);
    setPixmap(_pixmap);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(x / 100, y / 100);

    _body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    b2Vec2 vertices[4];
    vertices[0].Set(0,  (float)boundingRect().height() / 100);
    vertices[1].Set((float)boundingRect().width() / 100,  (float)boundingRect().height() / 100);
    vertices[2].Set((float)boundingRect().width() / 100, 0);
    vertices[3].Set(0, 0);

    shape.Set(vertices, 4);
    _body->CreateFixture(&shape, 0.0f);

}

Block::~Block()
{
    _body->DestroyFixture(_body->GetFixtureList());
    _body->GetWorld()->DestroyBody(_body);
}

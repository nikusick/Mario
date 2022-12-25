#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <Box2D/box2d.h>

#include "gameobject.h"

class Enemy: public ChangeableObject
{
    Q_OBJECT;
public:
    Enemy(qreal x, qreal y, qreal x1, qreal width, qreal step, const std::string& imgPath, b2World* world):
        ChangeableObject(x, y, width, step, imgPath) {
        setScale(1.5);
        _start = x;
        _stop = x1;

        //Set body
        setBody(x, y, world);

        //Set timer
        _colidingTimer = new QTimer;
        connect(_colidingTimer, SIGNAL(timeout()), this, SLOT(checkCollidings()));
        _colidingTimer->start();

        connect(timer, SIGNAL(timeout()), this, SLOT(move()));
        timer->start(100);
    }
    ~Enemy() {
        delete _colidingTimer;
        _body->GetWorld()->DestroyBody(_body);
    }

    virtual void advance(int phase) {
        if(phase) setPos(_body->GetPosition().x * 100, _body->GetPosition().y * 100);
    }
protected:
    qreal _start, _stop;
    QTimer* _colidingTimer;

    b2Body* _body;

    void setBody(qreal x, qreal y, b2World* world) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set((float)x / 100, (float)y / 100);
        bodyDef.fixedRotation = true;

        _body = world->CreateBody(&bodyDef);

        b2CircleShape cShape;
        cShape.m_radius = 0.1;
        cShape.m_p.Set((float)boundingRect().width()  * scale() / 200, ((float)boundingRect().height() * scale() - 10) / 100);


        b2FixtureDef fixtureDef;
        fixtureDef.shape = &cShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 10;
        _body->CreateFixture(&fixtureDef);
    }
    bool isTouchingMario(QGraphicsItem* item) {
        Mario* item1= dynamic_cast<Mario*>(item);
        return item1;
    }
    bool damageMario(QGraphicsItem* item) {
        QRectF marioRect(item->pos().x(), item->pos().y() + item->boundingRect().height(), item->boundingRect().width(), 10);
        QRectF otherRect(pos().x(), pos().y(), boundingRect().width(), 10);
        return !marioRect.intersects(otherRect);
    }

protected slots:
    void checkCollidings() {
        foreach(QGraphicsItem *item, collidingItems()) {
            if (isTouchingMario(item)) {
                if (!damageMario(item)) {
                    delete this;
                    return;
                }
            }
        }
    }
    void move() {
        if (pos().x() >= _stop) {
            site = 0;
        }
        if (pos().x() <= _start) {
            site = 1;
        }
        b2Vec2 vel = _body->GetLinearVelocity();
        vel.x = site ? 1.5: -1.5;
        _body->SetLinearVelocity( vel );
    }
};

class Turtle: public Enemy
{
public:
    Turtle(qreal x, qreal y, qreal x1, b2World* world):
        Enemy(x, y, x1, 45, 72, ":/characters/img/turtle.png", world){}
};

class Goomba: public Enemy
{
public:
    Goomba(qreal x, qreal y, qreal x1, b2World* world):
        Enemy(x, y, x1, 52, 54, ":/characters/img/goomba.png", world){}
};

class Spiny: public Enemy
{
public:
    Spiny(qreal x, qreal y, qreal x1, b2World* world):
        Enemy(x, y, x1, 120, 238, ":/characters/img/spiny.png", world){
        _colidingTimer->stop();
    }
};

class Piranha: public Enemy
{
public:
    Piranha(qreal x, qreal y, qreal x1, b2World* world):
        Enemy(x, y, x1, 130, 387, ":/characters/img/piranha.png", world){
        _colidingTimer->stop();
    }
};
#endif // ENEMY_H

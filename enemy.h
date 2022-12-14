#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <Box2D/box2d.h>

class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
protected:
    QPixmap _curPixmap;
    int _curFrame = 0;
    qreal _start, _stop;
    QTimer* _goTimer;
    QTimer* _colidingTimer;
    bool goLeft = false;

    b2Body* _body;

    void setBody(qreal x, qreal y, b2World* world);
    bool isTouchingMario(QGraphicsItem* item);
    bool damageMario(QGraphicsItem* item);

public:
    Enemy(qreal x, qreal y, qreal x1, qreal width, const std::string& img, b2World* world);
    ~Enemy();

    virtual void advance(int phase);

protected slots:
    virtual void changePixmap() = 0;
    void checkCollidings();
};

class Turtle: public Enemy
{
public:
    Turtle(qreal x, qreal y, qreal x1, b2World* world): Enemy(x, y, x1, 45, ":/characters/img/turtle.png", world){}
private:
    virtual void changePixmap() override {
        _curFrame += 72;
        if (_curFrame >= 1420 ) {
            _curFrame = 0;
        }
        if (pos().x() >= _stop) {
            goLeft = true;
        }
        if (pos().x() <= _start) {
            goLeft = false;
        }
        if (goLeft) {
            b2Vec2 vel = _body->GetLinearVelocity();
            vel.x = -1.5;
            _body->SetLinearVelocity( vel );
            setPixmap(_curPixmap.copy(_curFrame, 0, 45, 55));
        }
        else {
            b2Vec2 vel = _body->GetLinearVelocity();
            vel.x = 1.5;
            _body->SetLinearVelocity( vel );
            setPixmap(_curPixmap.copy(_curFrame, 0, 45, 55).transformed(
                          QTransform().scale(-1,1).translate(_curPixmap.copy(_curFrame, 0, 45, 55).width(), 0)));
        }
    }
};

class Goomba: public Enemy
{
public:
    Goomba(qreal x, qreal y, qreal x1, b2World* world): Enemy(x, y, x1, 52, ":/characters/img/goomba.png", world){}
private:
    virtual void changePixmap() override {
        _curFrame += 54;
        if (_curFrame >= 862) {
            _curFrame = 0;
        }
        if (pos().x() >= _stop) {
            goLeft = true;
        }
        if (pos().x() <= _start) {
            goLeft = false;
        }
        if (goLeft) {
            b2Vec2 vel = _body->GetLinearVelocity();
            vel.x = -1.5;
            _body->SetLinearVelocity( vel );
            setPixmap(_curPixmap.copy(_curFrame, 0, 52, 50));
        }
        else {
            b2Vec2 vel = _body->GetLinearVelocity();
            vel.x = 1.5;
            _body->SetLinearVelocity( vel );
            setPixmap(_curPixmap.copy(_curFrame, 0, 52, 50).transformed(
                          QTransform().scale(-1,1).translate(_curPixmap.copy(_curFrame, 0, 52, 50).width(), 0)));
        }
    }
};

class Spiny: public Enemy
{
public:
    Spiny(qreal x, qreal y, qreal x1, b2World* world): Enemy(x, y, x1, 120, ":/characters/img/spiny.png", world){
        _colidingTimer->stop();
    }
private:
    virtual void changePixmap() override {
        _curFrame += 238;
        if (_curFrame >= 3569) {
            _curFrame = 0;
        }
        if (pos().x() >= _stop) {
            goLeft = true;
        }
        if (pos().x() <= _start) {
            goLeft = false;
        }
        if (goLeft) {
            b2Vec2 vel = _body->GetLinearVelocity();
            vel.x = -1.5;
            _body->SetLinearVelocity( vel );
            setPixmap(_curPixmap.copy(_curFrame, 0, 120, 78));
        }
        else {
            b2Vec2 vel = _body->GetLinearVelocity();
            vel.x = 1.5;
            _body->SetLinearVelocity( vel );
            setPixmap(_curPixmap.copy(_curFrame, 0, 120, 78).transformed(
                          QTransform().scale(-1,1).translate(_curPixmap.copy(_curFrame, 0, 120, 78).width(), 0)));
        }
    }
};

class Piranha: public Enemy
{
public:
    Piranha(qreal x, qreal y, qreal x1, b2World* world): Enemy(x, y, x1, 130, ":/characters/img/piranha.png", world){
        _colidingTimer->stop();
    }
private:
    virtual void changePixmap() override {
        _curFrame += 387;
        if (_curFrame >= 9286) {
            _curFrame = 0;
        }
        setPixmap(_curPixmap.copy(_curFrame, 0, 130,165));
    }
};
#endif // ENEMY_H

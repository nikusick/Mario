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
    Turtle(qreal x, qreal y, qreal x1, b2World* world): Enemy(x, y, x1, 45, ":/characters/img/turtle.png", world){
    }
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
            setPixmap(_curPixmap.copy(_curFrame, 0, 45, 75));
        }
        else {
            b2Vec2 vel = _body->GetLinearVelocity();
            vel.x = 1.5;
            _body->SetLinearVelocity( vel );
            setPixmap(_curPixmap.copy(_curFrame, 0, 45, 75).transformed(
                          QTransform().scale(-1,1).translate(_curPixmap.copy(_curFrame, 0, 45, 75).width(), 0)));
        }
        checkCollidings();
    }
};

#endif // ENEMY_H

#ifndef MARIO_H
#define MARIO_H

#include <Box2D/box2d.h>
#include <QGraphicsPixmapItem>

#include "health.h"
#include "score.h"
#include "mediaplayer.h"

#define MARIO_IMG_PATH ":/characters/img/mario.png"
#define MARIO_VELOCITY 2


class Mario : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Mario(qreal x, qreal y, int height, b2World* world, MediaPlayer* player);
    ~Mario();

    void jump();
    void goLeft();
    void goRight();
    void stay();
    void blink();

    void changePixmap();

    Health* getHealth() const;
    Score* getScore() const;

    virtual void advance(int phase);
private:
    struct Condition {
       enum class Site {
           left, right
       };
       enum class Position {
           run, stay
       };
       Site site = Site::right;
       Position position = Position::stay;
    };
    Condition* _condition;
    Health* _health;
    Score* _score;
    MediaPlayer* _player;

    void setSite(Condition::Site);
    void setPosition(Condition::Position);

    b2Body* _body;
    b2World* _world;

    QPixmap _curPixmap;
    int _curFrame;

    QTimer* _goTimer;
    QTimer* _collidingTimer;
    QTimer* _damageTimer;

    int blinking_count = 0;

    //Collisions
    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouching(QGraphicsItem *item);
    bool isTouchingPlatform();
    bool isTouchingCoin(QGraphicsItem *item);
    bool isTouchingQuestbox(QGraphicsItem* item);

    //Collisions with enemies
    bool isTouchingEnemy(QGraphicsItem *item);
    bool killEnemy(QGraphicsItem *item);

private slots:
    void move();
    void blinking();

    void checkCollisions();
};

#endif // MARIO_H

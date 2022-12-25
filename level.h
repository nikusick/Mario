#ifndef LEVEL_H
#define LEVEL_H
#include "mario.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <Box2D/box2d.h>

#include <QFile>
#include <QTimer>

#include "timer.h"
#include "enemy.h"
#include "gameobject.h"
#include "mediaplayer.h"

#define MARIO_HEIGHT 100

class Level: public QGraphicsScene
{
    Q_OBJECT
public:
    Level(qreal height, int lvl, b2World* world, MediaPlayer* player);
    ~Level();

    Mario* _mario;

    void moveMenu(QPointF pos);
    int getTime();

    friend class Mario;
private:
    int _lvl;
    MediaPlayer* _player;

    b2World* _world;

    QTimer* _advTimer;
    Timer* _gameTimer;

    QGraphicsItemGroup* _menu;

    void setMap(int height);
    void setMenu();
public slots:
    void advance();
};

#endif // LEVEL_H

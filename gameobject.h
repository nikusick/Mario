#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include "mario.h"


class GameObject: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
public:
    GameObject(qreal x, qreal y, qreal width, const std::string& imgPath) {
        _pixmap = QPixmap(QString::fromStdString(imgPath));
        if (width == 0) setPixmap(_pixmap);
        else setPixmap(_pixmap.copy(0, 0, width, _pixmap.height()));
        setPos(x, y);
    };
protected:
    QPixmap _pixmap;
};

class Block: public GameObject
{
    Q_OBJECT;
public:
    Block(qreal x, qreal y, const std::string& imgPath, b2World* world):
        GameObject(x, y, 0, imgPath) {

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
    ~Block() {
        _body->DestroyFixture(_body->GetFixtureList());
        _body->GetWorld()->DestroyBody(_body);
    }
protected:
    b2Body* _body;
};

class QuestBox: public Block
{
    Q_OBJECT;
public:
    QuestBox(qreal x, qreal y, b2World* world):
        Block(x, y, ":/tiles/img/questbox_1.png", world){}
    bool full = true;
};

class BackgroundItem: public GameObject
{
    Q_OBJECT;
public:
    BackgroundItem(qreal x, qreal y, int blockSize, const std::string& imgPath):
        GameObject(x, y, 0, imgPath) {
        setPos(x * blockSize, (y + 1) * blockSize - _pixmap.height() % blockSize);
    }
};

class ChangeableObject: public GameObject
{
    Q_OBJECT;
public:
    ChangeableObject(qreal x, qreal y, qreal width, qreal step, const std::string& imgPath):
        GameObject(x, y, width, imgPath),
        _width(width), _step(step) {
        _maxWidth = _pixmap.width() * scale();
        _height = _pixmap.height() * scale();

        timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(changePixmap()));
    };
    ~ChangeableObject() {
        delete timer;
    }
protected:
    qreal _width, _height, _step, _maxWidth;
    int curFrame = 0;
    int site = 1;
    QTimer* timer;
protected slots:
    void changePixmap() {
        curFrame += _step;
        if (curFrame >= _maxWidth ) {
            curFrame = 0;
        }
        if (site) setPixmap(_pixmap.copy(curFrame, 0, _width, _height).
                       transformed(QTransform().scale(-1,1).translate(_width, 0)));
        else setPixmap(_pixmap.copy(curFrame, 0, _width, _height));
    }
};

class Coin: public ChangeableObject
{
    Q_OBJECT;
public:
    Coin(qreal x, qreal y): ChangeableObject(x, y, 39, 38, ":/tiles/img/coin.png") {
        connect(timer, SIGNAL(timeout()), this, SLOT(checkCollidings()));
        timer->start(100);
    }
private slots:
    void checkCollidings() {
        if (!collidingItems().empty()) {
            foreach(QGraphicsItem *item, collidingItems()) {
                Mario* item1= dynamic_cast<Mario*>(item);
                if (item1) {
                    setVisible(false);
                    return;
                }
            }
        }
    }
};


#endif // GAMEOBJECT_H

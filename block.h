#ifndef BLOCK_H
#define BLOCK_H

#include <Box2D/box2d.h>
#include <QGraphicsPixmapItem>
#include <QTimer>

#define TILES_PATH ":/tiles/"


class Block: public QObject, public QGraphicsPixmapItem
{
public:
    Block(qreal x, qreal y, const std::string& img, b2World* world);
    ~Block();
protected:
    b2Body* _body;
    QPixmap _pixmap;
};

#endif // BLOCK_H

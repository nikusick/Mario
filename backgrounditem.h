#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsPixmapItem>
#include <QTimer>

#include "mario.h"

#define TILES_PATH ":/tiles/img/"


class BackgroundItem: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
public:
    BackgroundItem(qreal x, qreal y, int blockSize, const std::string& imgPath) {
        _pixmap = QPixmap(QString::fromStdString(TILES_PATH + imgPath));
        setPixmap(_pixmap);
        setPos(x * blockSize, (y + 1) * blockSize - _pixmap.height() % blockSize);
    }
protected:
     QPixmap _pixmap;
};

class Coin: public BackgroundItem
{
    Q_OBJECT;
public:
    Coin(qreal x, qreal y, int blockSize, const std::string& imgPath): BackgroundItem(x, y, blockSize, imgPath) {
        timer = new QTimer;
        setPixmap(_pixmap.copy(curFrame, 0, 39, 41));
        connect(timer, SIGNAL(timeout()), this, SLOT(changePixmap()));
        timer->start(100);
    }
    ~Coin() {
        delete timer;
    }
private:
    int curFrame = 0;
    QTimer* timer;
private slots:
    void changePixmap() {
        curFrame += 38;
        if (curFrame >= 300 ) {
            curFrame = 0;
        }
        setPixmap(_pixmap.copy(curFrame, 0, 39, 41));
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

#endif // BACKGROUNDITEM_H

#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsItem>

class Health : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
public:
    Health() {
        decreaseHealth(0);
    }
    void decreaseHealth(int count) {
        _health -= count;
        setPixmap(_img.copy(0, 0, _health * 69, _img.height()));
    }
    int getHealth() {
        return _health;
    }
private:
    QPixmap _img = QPixmap(":/other/img/health_heart.png");
    int _health = 3;
};

#endif // HEALTH_H

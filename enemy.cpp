#include "mario.h"
#include "enemy.h"

Enemy::Enemy(qreal x, qreal y, qreal x1, qreal width, const std::string& img, b2World* world)
{
    //Set pixmap
    _curPixmap = QPixmap(QString::fromStdString(img));
    setPixmap(_curPixmap.copy(_curFrame, 0, width, 66));
    setScale(1.5);

    //Set position
    _start = x;
    _stop = x1;
    setPos(x, y);

    //Set body
    setBody(x, y, world);

    //Set timer
    _goTimer = new QTimer;
    connect(_goTimer, SIGNAL(timeout()), this, SLOT(changePixmap()));
    _goTimer->start(100);

    _colidingTimer = new QTimer;
    connect(_colidingTimer, SIGNAL(timeout()), this, SLOT(checkCollidings()));
    _colidingTimer->start();
}

Enemy::~Enemy()
{
    delete _goTimer;
    delete _colidingTimer;
    _body->GetWorld()->DestroyBody(_body);
}

void Enemy::advance(int phase)
{
    if(phase) {
        setPos(_body->GetPosition().x * 100, _body->GetPosition().y * 100);
    }
}

void Enemy::setBody(qreal x, qreal y, b2World *world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((float)x / 100, (float)y / 100);
    bodyDef.fixedRotation = true;

    _body = world->CreateBody(&bodyDef);

    b2CircleShape cShape;
    cShape.m_radius = 0.1;
    cShape.m_p.Set((float)pixmap().width() / 200, ((float)pixmap().height() * scale() - 20) / 100);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &cShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 10;
    _body->CreateFixture(&fixtureDef);
}

bool Enemy::isTouchingMario(QGraphicsItem* item)
{
    Mario* item1= dynamic_cast<Mario*>(item);
    return item1;
}

bool Enemy::damageMario(QGraphicsItem *item)
{
    QRectF marioRect(item->pos().x(), item->pos().y() + item->boundingRect().height(), item->boundingRect().width(), 10);
    QRectF otherRect(pos().x(), pos().y(), boundingRect().width(), 10);
    return !marioRect.intersects(otherRect);
}

void Enemy::checkCollidings()
{
    foreach(QGraphicsItem *item, collidingItems()) {
        if (isTouchingMario(item)) {
            if (!damageMario(item)) {
                delete this;
                return;
            }
        }
    }
}


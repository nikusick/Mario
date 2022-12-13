#include "mario.h"
#include "enemy.h"
#include "backgrounditem.h"
#include "block.h"
#include <QTimer>

float fromB2(float value) {
    return value * 100;
}

float toB2(float value) {
    return value / 100;
}

Mario::Mario(qreal x, qreal y, int height, b2World *world, MediaPlayer* player): _player(player), _world(world)
{
    _curPixmap = QPixmap(MARIO_IMG_PATH);
    _curFrame = 0;
    setPixmap(_curPixmap.copy(_curFrame, 0, 45, 75));
    setPos(x, y);
    setScale((float)height / 75);
    setZValue(1000);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(x / 100, y / 100);

    _body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    b2Vec2 vertices[1];
    vertices[0].Set(0,  (float)boundingRect().height() / 50 - 0.55);
    vertices[1].Set((float)boundingRect().width() / 75,  (float)boundingRect().height() / 50 - 0.55);
    vertices[2].Set((float)boundingRect().width() / 75, 0.1);
    vertices[3].Set(0, 0.1);

    shape.Set(vertices, 4);

    b2CircleShape cShape;
    cShape.m_radius = (float)boundingRect().width() / 200;
    cShape.m_p.y = 1.03 * (float)boundingRect().height() / 100;
    cShape.m_p.x = (float)boundingRect().width() / 200;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &cShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 10;
    _body->CreateFixture(&fixtureDef);
    _body->CreateFixture(&shape, 1.0f);

    _goTimer = new QTimer;
    _collidingTimer = new QTimer;
    _damageTimer = new QTimer;
    connect(_goTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(_collidingTimer, SIGNAL(timeout()), this, SLOT(checkCollisions()));
    connect(_damageTimer, SIGNAL(timeout()), this, SLOT(blinking()));

    _collidingTimer->start();

    _condition = new Condition;
    _health = new Health();
    _score = new Score;
}

Mario::~Mario()
{
    _body->GetWorld()->DestroyBody(_body);
    delete _goTimer;
    delete _damageTimer;
    delete _collidingTimer;
    delete _condition;
    delete _health;
    delete _score;
}

void Mario::advance(int phase)
{
    if(phase) {
        setPos(fromB2(_body->GetPosition().x), fromB2(_body->GetPosition().y));
    }
}

void Mario::setSite(Condition::Site st)
{
    if (_condition->site == st) {
           return;
    }
    _condition->site = st;
    changePixmap();
}

void Mario::setPosition(Condition::Position pos)
{
    if (_condition->position == pos) {
        return;
    }
    _condition->position = pos;
    changePixmap();
}

void Mario::changePixmap()
{
    if (_condition->position == Condition::Position::run) _curFrame += 57;
    else _curFrame = 0;
    if (_curFrame > 1191) _curFrame = 0;
    if (_condition->site == Condition::Site::left)
        setPixmap(_curPixmap.copy(_curFrame, 0, 45, 75).transformed(
                      QTransform().scale(-1,1).translate(_curPixmap.copy(_curFrame, 0, 45, 75).width(), 0)));
    else {
        setPixmap(_curPixmap.copy(_curFrame, 0, 45, 75));
    }
}

void Mario::jump()
{
    setPosition(Condition::Position::stay);
    b2Vec2 vel = _body->GetLinearVelocity();
    if (vel.y == 0) {
        _player->jump();
        vel.y = -8;
    }
    _body->SetLinearVelocity( vel );
}

void Mario::goLeft()
{
    setSite(Condition::Site::left);
    setPosition(Condition::Position::run);
    _goTimer->start(25);
}

void Mario::goRight()
{
    setSite(Condition::Site::right);
    setPosition(Condition::Position::run);
    _goTimer->start(25);
}

void Mario::move()
{
    b2Vec2 vel = _body->GetLinearVelocity();
    if (_condition->site == Condition::Site::left) {if (pos().x() > 0) vel.x = -MARIO_VELOCITY;}
    else vel.x = MARIO_VELOCITY;
    _body->SetLinearVelocity( vel );
    changePixmap();
}

void Mario::stay()
{
    _goTimer->stop();
    setPosition(Condition::Position::stay);
}

void Mario::blink()
{
    _damageTimer->start(200);
}

Health* Mario::getHealth() const
{
    return _health;
}

Score* Mario::getScore() const
{
    return _score;
}

// Collisions //-------------------------------
bool Mario::isTouchingFoot(QGraphicsItem *item) {
    QRectF rect(pos().x(), (pos().y() + 145), 90, 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 5);
    return rect.intersects(otherRect);
}

bool Mario::isTouching(QGraphicsItem *item) {
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    QRectF rect(pos().x(), pos().y(), 90, 150);
    return rect.intersects(otherRect);
}

bool Mario::isTouchingPlatform() {
    return pos().y() + 150 >= 950;
}

bool Mario::isTouchingCoin(QGraphicsItem *item)
{
    Coin* item1= dynamic_cast<Coin*>(item);
    return item1;
}

bool Mario::isTouchingQuestbox(QGraphicsItem *item)
{
    QuestBox* item1= dynamic_cast<QuestBox*>(item);
    if (item1 && item1->full) {
        item1->full = false;
        return true;
    }
    return false;
}


// Collisions with enemies //------------------
bool Mario::isTouchingEnemy(QGraphicsItem *item) {
    Enemy* item1= dynamic_cast<Enemy*>(item);
    return item1 && item->isVisible() && !_damageTimer->isActive();
}

bool Mario::killEnemy(QGraphicsItem *item)
{
    return isTouchingEnemy(item) && isTouchingFoot(item);
}

void Mario::blinking()
{
    blinking_count++;
    if (blinking_count == 10) {
        setVisible(true);
        blinking_count = 0;
        _damageTimer->stop();
    }
    else {
        setVisible(!isVisible());
    }
}


void Mario::checkCollisions()
{
    if (pos().x() <= 0) {
        auto vel =_body->GetLinearVelocity();
        vel.x = 0;
        _body->SetLinearVelocity( vel );
    }
    if (pos().y() <= 0) {
        auto vel =_body->GetLinearVelocity();
        vel.y = 0;
        _body->SetLinearVelocity( vel );
    }
    if (!collidingItems().empty()) {
        foreach(QGraphicsItem *item, collidingItems()) {
            if (isTouchingEnemy(item)) {
                if (!killEnemy(item)) {
                    _health->decreaseHealth(1);
                    blink();
                }
            }
            if (isTouchingQuestbox(item) && _health->getHealth() < 5) {
                _health->decreaseHealth(-1);
            }
            if (isTouchingCoin(item)) {
                _score->increase();
                _player->coin();
            }
        }
    }
}

#include "level.h"

Level::Level(qreal height, int lvl, b2World* world, MediaPlayer* player): _lvl(lvl), _player(player), _world(world)
{
    setMap(height);
    setMenu();

    _advTimer = new QTimer;
    connect(_advTimer, SIGNAL(timeout()), this, SLOT(advance()));
    _advTimer->start(1000 / 60);
}

Level::~Level()
{
    delete _advTimer;
}

void Level::moveMenu(QPointF pos)
{
    _menu->setPos(pos);
}

int Level::getTime()
{
    return _gameTimer->getTime();
}

void Level::setMap(int height)
{
    QFile file(QString::fromStdString(":/maps/maps/lvl_" + std::to_string(_lvl)));
    file.open(QIODevice::ReadOnly|QIODevice::Text);

    int blockSize = std::stoi(file.readLine().data());
    int w_block_count = std::stoi(file.readLine().data());
    int h_block_count = std::stoi(file.readLine().data());

    setSceneRect(QRect(0, 0, w_block_count * blockSize, height));

    _menu = new QGraphicsItemGroup;

    //   background   //
    auto background = file.readLine();
    background.remove(background.length() - 1, 1);
    auto img = QPixmap(QString(background)).scaledToHeight(height);
    _menu->addToGroup(new QGraphicsPixmapItem(img));

    QByteArray line;

    for (int i = 0; i < h_block_count; ++i) {
        line = file.readLine();
        for (int j = 0; j < w_block_count; ++j) {
            switch(line[j]) {
            case '1':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/winter_ground.png", _world));
                break;
            case '2':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/brick.png", _world));
                break;
            case '3':
            {
                addItem(new BackgroundItem(j, i, blockSize, ":/tiles/img/castle.png"));
                auto item = new BackgroundItem(j + (float)157 / blockSize, i, blockSize, ":/tiles/img/hcastle.png");
                item->setZValue(2000);
                addItem(item);
                break;
            }
            case '5':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/winter_ball.png", _world));
                break;
            case '6':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/winter_ground_1.png", _world));
                break;
            case 'c':
                addItem(new Coin(j * blockSize, i * blockSize));
                break;
            case 'f':
                addItem(new BackgroundItem(j, i, blockSize,  ":/tiles/img/flower.png"));
                break;
            case 's':
                addItem(new BackgroundItem(j, i, blockSize,  ":/tiles/img/sign.png"));
                break;
            case 'S':
                addItem(new Spiny(j * blockSize, i * blockSize, (j + 8) * blockSize, _world));
                break;
            case '4':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/stairblock.png", _world));
                break;
            case '7':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/wallf2.png", _world));
                break;
            case '8':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/walli.png", _world));
                break;
            case '9':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/ground.png", _world));
                break;
            case 'm':
                _mario = new Mario(j * blockSize, i * blockSize, MARIO_HEIGHT, _world, _player);
                addItem(_mario);
                break;
            case 't':
                addItem(new Turtle(j * blockSize, i * blockSize, (j + 3) * blockSize, _world));
                break;
            case 'q':
                addItem(new QuestBox(j * blockSize, i * blockSize, _world));
                break;
            case 'g':
                addItem(new Goomba(j * blockSize, i * blockSize, (j + 4) * blockSize, _world));
                break;
            case 'p':
                addItem(new Piranha(j * blockSize, i * blockSize, 0, _world));
                break;
            case 'w':
                addItem(new Block(j * blockSize, i * blockSize, ":tiles/img/warp.png", _world));
                break;
            }
        }
    }
}

void Level::setMenu()
{
    auto clock = new QGraphicsPixmapItem(QPixmap(":/other/img/clock.png"));
    clock->setPos(0, 0);
    _menu->addToGroup(clock);
    _gameTimer = new Timer();
    _gameTimer->setPos(50, 0);
    _menu->addToGroup(_gameTimer);

    _mario->getHealth()->setPos(150, 0);
    _menu->addToGroup(_mario->getHealth());

    _mario->getScore()->setPos(550, 0);
    _menu->addToGroup(_mario->getScore());
    _menu->setZValue(-1);
    addItem(_menu);
}


void Level::advance()
{
    _world->Step(1.00f / 60.00f, 6, 2);
    QGraphicsScene::advance();
}

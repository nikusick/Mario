#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    setWindowTitle(tr("Super Mario"));
    setFixedSize(width(), height());

    setMenu();
    setView();
    setSettings();

    _player = new MediaPlayer;

    _world = new b2World(b2Vec2(0.00f, 10.00f));

    _timer = new QTimer;
    connect(_timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
}

MainWindow::~MainWindow()
{
    delete _ui;
    if (inGame) delete _level;
    delete _timer;
    delete _world;
    delete _player;
}

void MainWindow::setView()
{
    _ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _ui->graphicsView->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::setMenu()
{
    _ui->stackedWidget->setAutoFillBackground(true);
    QPixmap pixmap=QPixmap(":/maps_backgrounds/img/menu_background.jpg").scaled(_ui->stackedWidget->size());
    QPalette palette(_ui->stackedWidget->palette());
    palette.setBrush(_ui->stackedWidget->backgroundRole(),QBrush(pixmap.scaled(_ui->stackedWidget->size(),
                                                                               Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    _ui->stackedWidget->setPalette(palette);
    _ui->stackedWidget->setCurrentWidget(_ui->menu);
}

void MainWindow::setWinPage()
{
    _ui->label_5->setText("Time: " + QString::number(_level->getTime()) +
                          "\nScore: " + QString::number(_level->_mario->getScore()->getScore()));
    inGame = false;
    _timer->stop();
    _ui->stackedWidget->setCurrentWidget(_ui->win_page);
    delete _level;
    _player->endGame();
    releaseKeyboard();
}

void MainWindow::setLosePage()
{
    inGame = false;
    _timer->stop();
    _ui->stackedWidget->setCurrentWidget(_ui->lose_page);
    delete _level;
    _player->endGame();
    releaseKeyboard();
}

void MainWindow::setSettings()
{
    _ui->keyUp->setKeySequence(_controls.at("up"));
    _ui->keyLeft->setKeySequence(_controls.at("left"));
    _ui->keyRight->setKeySequence(_controls.at("right"));
}

void MainWindow::setLevel(int lvl)
{
    _ui->stackedWidget->setCurrentWidget(_ui->game);

    grabKeyboard();
    inGame = true;

    _player->startGame();
    _level = new Level(_ui->graphicsView->height(), lvl, _world, _player);
    _ui->graphicsView->setScene(_level);
    _ui->graphicsView->centerOn(_level->_mario);
    _timer->start();
}

void MainWindow::moveCamera()
{
    _ui->graphicsView->centerOn(_level->_mario);
    _level->moveMenu(_ui->graphicsView->mapToScene(0, 0));
    if (_ui->graphicsView->mapFromScene(_level->_mario->pos()).x() >= _ui->graphicsView->width() - 25) {
        setWinPage();
    }
    else if (_level->getTime() == 0
             || _level->_mario->getHealth()->getHealth() == 0
             || _level->_mario->pos().y() >= _ui->graphicsView->height()) {
        setLosePage();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (inGame) {
        if (event->key() == _controls.at("up")) _level->_mario->jump();
        if (event->key() == _controls.at("left")) _level->_mario->goLeft();
        if (event->key() == _controls.at("right")) _level->_mario->goRight();
        if (event->key() == Qt::Key_Q) {
            inGame = false;
            _timer->stop();
            _ui->stackedWidget->setCurrentWidget(_ui->menu);
            delete _level;
            _player->endGame();
            releaseKeyboard();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat() && inGame) {
        _level->_mario->stay();
    }
}

void MainWindow::on_lvl_1_clicked()
{
    setLevel(1);
}

void MainWindow::on_lvl_2_clicked()
{
    setLevel(2);
}

void MainWindow::on_keyUp_keySequenceChanged(const QKeySequence &keySequence)
{
    _controls.at("up") = keySequence[0].key();
}


void MainWindow::on_settings_b_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->settings);
}


void MainWindow::on_save_b_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->menu);
}


void MainWindow::on_keyLeft_keySequenceChanged(const QKeySequence &keySequence)
{
    _controls.at("left") = keySequence[0].key();
}


void MainWindow::on_keyRight_keySequenceChanged(const QKeySequence &keySequence)
{
    _controls.at("right") = keySequence[0].key();
}


void MainWindow::on_to_menu_2_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->menu);
}


void MainWindow::on_to_menu_1_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->menu);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    _player->setMute(!arg1);
}

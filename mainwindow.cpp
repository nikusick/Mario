#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    setWindowTitle(tr("Super Mario"));
    setFixedSize(this->width(), this->height());
    setMenu();
    setView();
    setSettings();

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

void MainWindow::setLosePage()
{

}

void MainWindow::setWinPage()
{
    _ui->label_5->setText("Time: " + QString::number(_level->getTime()) +
                          "\nScore: " + QString::number(_level->_mario->getScore()->getScore()));
}

void MainWindow::setSettings()
{
    _ui->keyUp->setKeySequence(_controls.at("up"));
    _ui->keyLeft->setKeySequence(_controls.at("left"));
    _ui->keyRight->setKeySequence(_controls.at("right"));
}

void MainWindow::moveCamera()
{
    _ui->graphicsView->centerOn(_level->_mario);
    _level->moveMenu(_ui->graphicsView->mapToScene(0, 0));
    if (_level->_mario->pos().x() >= 4777) {
        inGame = false;
        _timer->stop();
        setWinPage();
        _ui->stackedWidget->setCurrentWidget(_ui->win_page);
        delete _level;
        releaseKeyboard();
    }
    else if (_level->getTime() == 0 || _level->_mario->getHealth()->getHealth() == 0) {
        inGame = false;
        _timer->stop();
        _ui->stackedWidget->setCurrentWidget(_ui->lose_page);
        delete _level;
        releaseKeyboard();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (inGame) {
        if (QKeySequence(event->key()) == _controls.at("up")) _level->_mario->jump();
        if (QKeySequence(event->key()) == _controls.at("left")) _level->_mario->goLeft();
        if (QKeySequence(event->key()) == _controls.at("right")) _level->_mario->goRight();
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
    _ui->stackedWidget->setCurrentWidget(_ui->game);

    grabKeyboard();
    inGame = true;

    _level = new Level(_ui->graphicsView->height(), 1, _world);
    _ui->graphicsView->setScene(_level);
    _ui->graphicsView->centerOn(_level->_mario);
    _timer->start();
}


void MainWindow::on_keyUp_keySequenceChanged(const QKeySequence &keySequence)
{
    _controls.at("up") = keySequence;
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
    _controls.at("left") = keySequence;
}


void MainWindow::on_keyRight_keySequenceChanged(const QKeySequence &keySequence)
{
    _controls.at("right") = keySequence;
}


void MainWindow::on_to_menu_2_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->menu);
}


void MainWindow::on_to_menu_1_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->menu);
}


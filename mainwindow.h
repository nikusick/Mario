#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QMovie>
#include "level.h"
#include <Box2D/box2d.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;

    Level* _level;
    QTimer* _timer;
    b2World* _world;

    bool inGame = false;

    std::map<std::string, QKeySequence> _controls = {
        {"up", Qt::Key_Up},
        {"left", Qt::Key_Left},
        {"right", Qt::Key_Right}
    };

    void setView();
    void setMenu();
    void setLosePage();
    void setWinPage();
    void setSettings();

private slots:
    void moveCamera();

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    //Menu buttons
    void on_settings_b_clicked();
    void on_lvl_1_clicked();

    //Settings buttons
    void on_keyUp_keySequenceChanged(const QKeySequence &keySequence);
    void on_keyLeft_keySequenceChanged(const QKeySequence &keySequence);
    void on_keyRight_keySequenceChanged(const QKeySequence &keySequence);
    void on_save_b_clicked();
    void on_to_menu_2_clicked();
    void on_to_menu_1_clicked();
};
#endif // MAINWINDOW_H

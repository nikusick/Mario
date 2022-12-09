#include "mainwindow.h"

#include <QApplication>
#include <box2d\box2d.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

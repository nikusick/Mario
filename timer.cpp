#include "timer.h"
#include <QTimer>
#include <QFont>
#include<QFontDatabase>


Timer::Timer(QGraphicsItem *parent): QGraphicsTextItem(parent){

    // initialize the coinCount to 400
    timeCount = 400;

    // draw the text
    setPlainText(QString("") + QString::number(timeCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("Sitka text",30));
    startTimer(1000);
}

void Timer::timerEvent(QTimerEvent *){
    decrease();
}

void Timer::decrease(){

    if(timeCount != 0){
        timeCount--;
        setPlainText(QString("") + QString::number(timeCount));
    }

}

int Timer::getTime(){
    return timeCount;

}

#include "score.h"
#include <QFont>
#include<QFontDatabase>


Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the coinCount to 0
    scoreCount = 0;

    // draw the text
    setPlainText(QString("Score: ") + QString::number(scoreCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("Sitka Text",30));


}

void Score::increase(){
    scoreCount++;
    setPlainText(QString("Score: ") + QString::number(scoreCount));
}

int Score::getScore(){
    return scoreCount;
}

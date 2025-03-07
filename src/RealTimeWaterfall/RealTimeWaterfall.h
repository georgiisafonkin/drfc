#ifndef REALTIMEWATERFALL_H
#define REALTIMEWATERFALL_H

#include <QGraphicsScene>
#include <QWidget>
#include <qgraphicsitem.h>
#include "../LoopedList/LoopedList.h"

//класс для отрисовки водопада

//толком ничего не написано, поэтому, возможно, стоит начать писать его с нуля

class RealTimeWaterFall : public QWidget
{
    Q_OBJECT
public:
    explicit RealTimeWaterFall(QWidget *parent = nullptr);
    void setImage(LoopedList<QList<qint16>> data);
private:
    QGraphicsScene* waterfallGS = new QGraphicsScene(this);
    QImage waterfallImg; //TODO: инициализация с размерами
    QPixmap waterfallPixmap = QPixmap::fromImage(waterfallImg);
    QGraphicsPixmapItem* waterfallPxMpItem = new QGraphicsPixmapItem(waterfallPixmap);

signals:
};

#endif // REALTIMEWATERFALL_H

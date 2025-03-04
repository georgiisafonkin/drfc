#include "RealTimeWaterfall.h"

RealTimeWaterFall::RealTimeWaterFall(QWidget *parent)
    : QWidget{parent}
{}

void RealTimeWaterFall::setImage(LoopedList<QList<qint16>> data) {
    this->waterfallImg = QImage(data.getData().at(0).size(), data.getSize(), QImage::Format_RGB888);

    qint16 minValue = 2432, maxValue = -2432; //Минимальное и максимальное значение рефлектограмм

    for (const auto& row : data) {
        for (qint16 value : row) {
            minValue = qMin(minValue, value);
            maxValue = qMax(maxValue, value);
        }
    }
}

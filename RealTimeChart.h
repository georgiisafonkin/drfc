#ifndef REALTIMECHART_H
#define REALTIMECHART_H

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QWidget>
#include <QTimer>

#include <qchart.h>
#include <qchartview.h>
#include <qlineseries.h>

QT_CHARTS_USE_NAMESPACE

class RealTimeChart : public QWidget
{
    Q_OBJECT
public:
    explicit RealTimeChart(QWidget *parent = nullptr);
    void updateChart(const std::vector<qint16>& numbers);
private:
    QChart* chart;
    QLineSeries* series;
    QChartView* chartView;
    QTimer* timer;
    int counter;
signals:
};

#endif // REALTIMECHART_H

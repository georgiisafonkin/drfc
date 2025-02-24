#ifndef REALTIMECHART_H
#define REALTIMECHART_H

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QWidget>
#include <QTimer>

#include <QRunnable>
#include <qchart.h>
#include <qchartview.h>
#include <qlineseries.h>

QT_CHARTS_USE_NAMESPACE

class RealTimeChart : public QWidget
{
    Q_OBJECT
public:
    explicit RealTimeChart(QWidget *parent = nullptr);
    void updateChart(const QList<quint16>& numbers);
private:
    QChart* chart;
    QLineSeries* series;
    QChartView* chartView;
    int curChartIndex;
    int counter = 0;
    std::vector<quint16> numbers;
signals:
};

#endif // REALTIMECHART_H

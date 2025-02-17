#include "RealTimeChart.h"
#include <QVBoxLayout>
#include <qdebug.h>

RealTimeChart::RealTimeChart(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "new RealTimeChart was created.";
    series = new QtCharts::QLineSeries;
    chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->setTitle("Reflectogram");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
}

void RealTimeChart::updateChart(const QList<quint16>& numbers) {
    series->clear();

    quint16 maxVertVal = 0;

    quint32 i = 0;
    while (i < numbers.size()) {
        maxVertVal = qMax(maxVertVal, numbers.at(i));
        series->append(i, numbers.at(i));
        ++i;
    }

    chart->axes(Qt::Horizontal).first()->setRange(0, numbers.size());
    chart->axes(Qt::Vertical).first()->setRange(0, maxVertVal);

    chartView->repaint();
    chart->update();
    layout()->update();
}

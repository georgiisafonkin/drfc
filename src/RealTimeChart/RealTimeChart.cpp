#include "RealTimeChart.h"
#include <QVBoxLayout>
#include <qdebug.h>

RealTimeChart::RealTimeChart(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "new RealTimeChart was created.";
    series = new QtCharts::QLineSeries();
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

    if (!chart->axes(Qt::Vertical).isEmpty()) {
        chart->axes(Qt::Vertical).first()->setRange(-256, 256);
    }
}

void RealTimeChart::updateChart(const QList<qint16>& numbers) {
    QVector<QPointF> points;
    points.reserve(numbers.size());

    qint16 maxVertVal = 0;
    qint16 minVertVal = 0;

    for (int i = 0; i < numbers.size(); ++i) {
        maxVertVal = qMax(maxVertVal, numbers.at(i));
        minVertVal = qMin(minVertVal, numbers.at(i));
        points.append(QPointF(i, numbers.at(i)));
    }

    series->replace(points);

    if (!chart->axes(Qt::Horizontal).isEmpty()) {
        chart->axes(Qt::Horizontal).first()->setRange(0, numbers.size());
    }
}

QChartView *RealTimeChart::getChartView() const
{
    return chartView;
}

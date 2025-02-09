#include "RealTimeChart.h"
#include <QVBoxLayout>
#include <qdebug.h>

RealTimeChart::RealTimeChart(QWidget *parent)
    : QWidget{parent}, counter(0)
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

    // Set up a timer to simulate real-time updates
    // timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &RealTimeChart::updateChart);
    // timer->start(100);  // Update every 100 ms
}

void RealTimeChart::updateChart(const std::vector<qint16>& numbers) {
    int minVal = *std::min_element(numbers.begin(), numbers.end());
    int maxVal = *std::max_element(numbers.begin(), numbers.end());

    for (int i = 0; i < numbers.size(); ++i) {
        series->append(counter + i, numbers.at(i));
    }
    counter += numbers.size();

    chart->axes(Qt::Horizontal).first()->setRange(0, counter);
    chart->axes(Qt::Vertical).first()->setRange(minVal, maxVal);
    chart->update();
}

#ifndef GUI_H
#define GUI_H

#include "DataTransmissionWorker.h"
#include "RealTimeChart.h"
#include <QChart>
#include <QChartView>
#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class GUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit GUI(QWidget *parent = nullptr);

private:
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QLabel* label;
    QComboBox* comPortCombo;
    QPushButton* refreshButton;
    QPushButton* selectButton;
    void refreshComPorts();
    void selectComPort();

    DataTransmissionHandler* dth;

    void updateCharts(int index, const std::vector<qint16>& numbers);
    int pointNumber = 0;

    std::vector<RealTimeChart*> realTimeCharts;
signals:
};

#endif // GUI_H

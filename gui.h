#ifndef GUI_H
#define GUI_H

#include "DataTransmissionHandler.h"
#include "FileWriter.h"
#include "RealTimeChart.h"
#include "src/MenuBar/MenuBar.h"
#include <QChart>
#include <QChartView>
#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QQueue>
#include <QSerialPort>
#include <QThreadPool>
#include <QVBoxLayout>
#include <QWidget>

class GUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit GUI(QWidget *parent = nullptr);
    ~GUI();
    QWaitCondition* queueNotEmpty;
private:
    //GUI stuff
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QLabel* label;
    QComboBox* comPortCombo;
    QPushButton* refreshButton;
    QPushButton* selectButton;
    MenuBar* menuBar;
    //Buttons stuff
    void refreshComPorts();
    void selectComPort();

    DataTransmissionHandler* dth;
    FileWriter* fw;

    //Charts, plotting stuff
    QQueue<QList<quint16>>* plotQueue;
    void updateChartsData(const QList<quint16>& numbers); //add chart to plotQueue
    void plotCharts();
    RealTimeChart* realTimeChart = new RealTimeChart();
    QMutex* queueMutex;
    QTimer* plotTimer;
signals:
};

#endif // GUI_H


//TODO: after ternination of main (GUI) thread other thread must terminate too

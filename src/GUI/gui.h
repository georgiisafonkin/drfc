#ifndef GUI_H
#define GUI_H

#include "../DataTransmissionHandler/DataTransmissionHandler.h"
#include "../FileWriter/FileWriter.h"
#include "../RealTimeChart/RealTimeChart.h"
#include "../MenuBar/MenuBar.h"
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

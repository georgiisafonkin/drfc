#ifndef GUI_H
#define GUI_H

#include "../DataTransmissionHandler/DataTransmissionHandler.h"
#include "../FileWriter/FileWriter.h"
#include "../RealTimeChart/RealTimeChart.h"
#include "../mainWindowDAS/mainWindowDAS.h"
#include "../LoopedList/LoopedList.h"
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
    Ui::MainWindow* uiDAS;

    //Buttons stuff
    void refreshComPorts();
    void selectComPort();
    void startReflRead();
    void stopReflRead();

    DataTransmissionHandler* dth;
    FileWriter* fw;

    //Charts, plotting stuff
    QQueue<QList<qint16>>* plotQueue;
    qint32 reflsListSize = 200;
    LoopedList<QList<qint16>>* reflsLoopedList;
    void updateChartsData(const QList<qint16>& numbers); //add chart to plotQueue
    void updateReflsLoopedList(const QList<qint16>& numbers); //refl to waterfall list
    void plotCharts();
    RealTimeChart* realTimeChart = new RealTimeChart();
    QMutex* queueMutex;
    QTimer* plotTimer;
signals:
};

#endif // GUI_H

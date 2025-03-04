#include "gui.h"

#include <QProcess>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <qdebug.h>
#include <QLineEdit>

GUI::GUI(QWidget *parent)
    : QMainWindow{parent}, uiDAS(new Ui::MainWindow()),
    plotQueue(new QQueue<QList<qint16>>()),
    reflsLoopedList(new LoopedList<QList<qint16>>(reflsListSize)),
    queueNotEmpty(new QWaitCondition()), queueMutex(new QMutex()), plotTimer(new QTimer(this))
{

    uiDAS->setupUi(this);
    uiDAS->setReflGV(realTimeChart->getChartView());

    connect(uiDAS->refreshPortsButton, &QPushButton::clicked, this, &GUI::refreshComPorts);

    connect(uiDAS->choosePortButtom, &QPushButton::clicked, this, &GUI::selectComPort);

    connect(uiDAS->startButton, &QPushButton::clicked, this, &GUI::startReflRead);

    connect(uiDAS->stopButton, &QPushButton::clicked, this, &GUI::stopReflRead);

    //separeted thread for data transmission, processing
    dth = new DataTransmissionHandler(this);

    fw = new FileWriter(this);

    refreshComPorts();

    connect(dth, &DataTransmissionHandler::ReflectogramDataReady, fw, &FileWriter::updateReflectogramData, Qt::QueuedConnection);
    connect(dth, &DataTransmissionHandler::ChartDataReady, this, &GUI::updateReflsLoopedList, Qt::QueuedConnection);
    connect(dth, &DataTransmissionHandler::ChartDataReady, this, &GUI::updateChartsData, Qt::QueuedConnection);

    connect(plotTimer, &QTimer::timeout, this, &GUI::plotCharts);
    plotTimer->start(10); //41ms for 24fps charts

}

void GUI::refreshComPorts() {
    uiDAS->comPortsComboBox->clear();

    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        uiDAS->comPortsComboBox->addItem(port.portName()) ;
    }
}

void GUI::startReflRead() {
    fw->start();

    dth->start();

    plotCharts();
}

void GUI::stopReflRead() {
    fw->requestInterruption();
    dth->requestInterruption();
}

void GUI::selectComPort() {
    QString selectedPort = uiDAS->comPortsComboBox->currentText();
    if (!selectedPort.isEmpty()) {
        qDebug() << "Selected COM Port:" << selectedPort;

        // fw->start();

        dth->setComPortName(selectedPort);
        // dth->start();

        // plotCharts();
    } else {
        qDebug() << "No COM Port selected.";
    }
}

 //charts below
void GUI::updateReflsLoopedList(const QList<qint16>& numbers) {
    reflsLoopedList->prepend(numbers);
}


void GUI::updateChartsData(const QList<qint16>& numbers) {
    plotQueue->enqueue(numbers);
}

void GUI::plotCharts() {
    // qDebug() << "GUI::plotCharts()";

    if (plotQueue->empty()) return;

    QList<qint16> plotData = plotQueue->dequeue();

    realTimeChart->updateChart(plotData);
}

GUI::~GUI() {
    dth->requestInterruption();
    dth->quit();
    dth->wait();

    fw->queueNotEmpty->wakeOne();  // Ensure it wakes up if waiting
    fw->requestInterruption();
    fw->quit();
    fw->wait();
}


//TODO: GUI класс содержит сгенерированный Ui::MainWindow, надо подвязать RealTimeChart к graphicsView и сигналы
//правильно связать

//TODO: свой циклический список на основе QVarLengthArray


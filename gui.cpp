#include "gui.h"

#include "DataTransmissionHandler.h"
#include "FileWriter.h"

#include <QProcess>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <qdebug.h>

GUI::GUI(QWidget *parent)
    : QMainWindow{parent}, plotQueue(new QQueue<QList<quint16>>()), queueNotEmpty(new QWaitCondition()), queueMutex(new QMutex())
{
    //separeted thread for data transmission, processing
    dth = new DataTransmissionHandler(this);

    fw = new FileWriter(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    label = new QLabel("Select a COM Port:", this);
    layout->addWidget(label);

    comPortCombo = new QComboBox(this);
    layout->addWidget(comPortCombo);

    refreshButton = new QPushButton("Refresh COM Ports", this);
    layout->addWidget(refreshButton);
    connect(refreshButton, &QPushButton::clicked, this, &GUI::refreshComPorts);

    selectButton = new QPushButton("Select", this);
    layout->addWidget(selectButton);
    connect(selectButton, &QPushButton::clicked, this, &GUI::selectComPort);

    realTimeChart->setMinimumHeight(720);
    layout->addWidget(realTimeChart);

    refreshComPorts();

    QObject::connect(dth, &DataTransmissionHandler::ReflectogramDataReady, fw, &FileWriter::updateReflectogramData, Qt::QueuedConnection);
    connect(dth, &DataTransmissionHandler::ChartDataReady, this, &GUI::updateChartsData, Qt::QueuedConnection);
}

void GUI::refreshComPorts() {
    comPortCombo->clear();

    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        comPortCombo->addItem(port.portName()) ;
    }
}

void GUI::selectComPort() {
    QString selectedPort = comPortCombo->currentText();
    if (!selectedPort.isEmpty()) {
        qDebug() << "Selected COM Port:" << selectedPort;

        fw->start();

        dth->setComPortName(selectedPort);
        dth->start();

        plotCharts();
    } else {
        qDebug() << "No COM Port selected.";
    }
}

 //charts below
void GUI::updateChartsData(const QList<quint16>& numbers) {
    qDebug() << "GUI::updateChartsData() was invoked by Thread with TID: " << QThread::currentThreadId();
    // QMutexLocker locker(queueMutex);
    plotQueue->enqueue(numbers);
    plotCharts();
    // QMetaObject::invokeMethod(this, "plotCharts", Qt::QueuedConnection);
    // queueNotEmpty->wakeOne();
}

void GUI::plotCharts() {
    qDebug() << "GUI::plotCharts()";
    // QMutexLocker locker(queueMutex);

    if (plotQueue->empty()) return;

    QList<quint16> plotData = plotQueue->dequeue();

    // locker.unlock();

    realTimeChart->updateChart(plotData);
    layout->update();
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

//TODO: sync primitive like in a file writer

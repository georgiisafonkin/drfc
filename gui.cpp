#include "gui.h"

#include "DataTransmissionWorker.h"

#include <QSerialPortInfo>
#include <qdebug.h>
#include <vector>

GUI::GUI(QWidget *parent)
    : QMainWindow{parent}
{
    //separeted thread for data transmission, processing
    dth = new DataTransmissionHandler();

    // Central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout
    layout = new QVBoxLayout(centralWidget);

    // Label
    label = new QLabel("Select a COM Port:", this);
    layout->addWidget(label);

    // ComboBox for COM ports
    comPortCombo = new QComboBox(this);
    layout->addWidget(comPortCombo);

    // Refresh button
    refreshButton = new QPushButton("Refresh COM Ports", this);
    layout->addWidget(refreshButton);
    connect(refreshButton, &QPushButton::clicked, this, &GUI::refreshComPorts);

    // Select button
    selectButton = new QPushButton("Select", this);
    layout->addWidget(selectButton);
    connect(selectButton, &QPushButton::clicked, this, &GUI::selectComPort);

    // Populate COM ports on startup
    refreshComPorts();

    // Signal-slot for drawing charts in real-time
    connect(dth, &DataTransmissionHandler::ChartDataReady, this, &GUI::updateCharts, Qt::QueuedConnection);
}

void GUI::refreshComPorts() {
    // Clear the ComboBox
    comPortCombo->clear();

    // Get available COM ports
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        comPortCombo->addItem(port.portName());
    }
}

void GUI::selectComPort() {
    QString selectedPort = comPortCombo->currentText();
    if (!selectedPort.isEmpty()) {
        qDebug() << "Selected COM Port:" << selectedPort;
        dth->start();
    } else {
        qDebug() << "No COM Port selected.";
    }
}

void GUI::updateCharts(int index, const std::vector<qint16>& numbers) {
    qDebug() << "Updating chart at index:" << index << "with data size:" << numbers.size();
    for (auto value : numbers) {
        qDebug() << value;
    }

    if (index == realTimeCharts.size()) {
        auto *newChart = new RealTimeChart();
        realTimeCharts.push_back(newChart);
        newChart->setMinimumHeight(300);
        layout->addWidget(newChart);
    }
    realTimeCharts.at(index)->updateChart(numbers);

    layout->update();
}

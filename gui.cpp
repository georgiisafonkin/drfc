#include "gui.h"

#include "DataTransmissionWorker.h"

#include <QSerialPortInfo>
#include <qdebug.h>

GUI::GUI(QWidget *parent)
    : QMainWindow{parent}
{
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
        DataTransmissionWorker* dtw = new DataTransmissionWorker();
        dtw->start();
    } else {
        qDebug() << "No COM Port selected.";
    }
}

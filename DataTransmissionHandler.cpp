#include "DataTransmissionHandler.h"
#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QProcess>
#include <QNetworkDatagram>
#include <QPair>

DataTransmissionHandler::DataTransmissionHandler(QObject *parent)
    : QThread{parent}
{
    elapsedTimer = QElapsedTimer();
}



QByteArray DataTransmissionHandler::createStartMessage() {
    static QByteArray message;

    // Start message creation
    message.append(static_cast<qint16>(1000 * Ng) >> 8);
    message.append(static_cast<qint16>(1000 * Ng) & 0xff);

    message.append(static_cast<qint16>(lineLength) >> 8);
    message.append(static_cast<qint16>(lineLength) & 0xff);

    message.append(static_cast<qint16>(lengthUdpPack) >> 8);
    message.append(static_cast<qint16>(lengthUdpPack) & 0xff);

    message.append(static_cast<qint16>(freqSendData) >> 8);
    message.append(static_cast<qint16>(freqSendData) & 0xff);

    message.append(static_cast<qint16>(pulseWidth) >> 8);
    message.append(static_cast<qint16>(pulseWidth) & 0xff);

    return message;
}

void DataTransmissionHandler::startDataTransmission() {
    QByteArray message = createStartMessage();
    sock->writeDatagram(message, message.size(), clAddress, clPort);
    qDebug() << "Start message sent to the card.";
}

void DataTransmissionHandler::recieveData() {
    elapsedTimer.start();
    while (!isInterruptionRequested()) {
        // while (true) {
        //     if (chosenPort->waitForReadyRead(1000)) {
        //         QByteArray datas = chosenPort->readAll();
        //         qDebug() << "from port: " << QString(datas);
        //     }
        // }

        QByteArray datagram;
        datagram.resize(lengthUdpPack + 5);  // Adjust size as needed

        // Receive the data from the socket
        QNetworkDatagram networkDatagram;
        networkDatagram = sock->receiveDatagram(lengthUdpPack + 5);
        if (networkDatagram.data().size() > 0) {
            // qDebug() << "Received data:" << networkDatagram.data();
            processReceivedData(networkDatagram.data());
        }
        else {
            if (elapsedTimer.elapsed() >= 10000) {
                qDebug() << "Can't receive any packet. Shut down...";
                processReceivedData();
                break;
            }
        }
    }
}

void DataTransmissionHandler::setComPortName(const QString &newComPortName)
{
    comPortName = newComPortName;
}

void DataTransmissionHandler::processReceivedData(const QByteArray &data) {
    elapsedTimer.restart();
    static int prevNumPack = 0;
    int numPack = int(data[1] << 8 | data[2]);
    // qDebug() << "numPack: " << numPack;
    if (numPack == 0) {
        if (index != 0) {
            QPair<quint16, QByteArray>* newPair = new QPair<quint16, QByteArray>(index, *array);
            emit ReflectogramDataReady(*newPair);
            ChartDataReady(prepareNumbers(*array));
            qDebug() << "DataTranslationHandler in Thread with TID " << QThread::currentThreadId() <<" emit signals";
            array->clear();
        }
        array->append(data.begin() + 5, lengthUdpPack);
        // qDebug() << "Array size: " << array->size() << "data size: " << data.size();
        prevNumPack = numPack;
        index += 1;
    }
    else if (numPack - prevNumPack == 1) {
        prevNumPack = numPack;
        array->append(data.data() + 5);
    }
    // qDebug() << "Processing received data of size:" << data.size();
}

void DataTransmissionHandler::processReceivedData() {
    ReflectogramDataReady(QPair<quint16, QByteArray>(index, *array));
    ChartDataReady(prepareNumbers(*array));
    array->clear();
}

void DataTransmissionHandler::connectToComPort() {
    // QString portName = comPortCombo->currentData().toString();
    chosenPort->setPortName(comPortName);
    chosenPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    chosenPort->setDataBits(QSerialPort::Data8);
    chosenPort->setParity(QSerialPort::NoParity);
    chosenPort->setStopBits(QSerialPort::OneStop);
    chosenPort->setFlowControl(QSerialPort::NoFlowControl);

    if (chosenPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Successfully connected to COM port: " + comPortName;
    } else {
        qDebug() << "Failed to connect to COM port: " + comPortName;
        qDebug() << "Port Error: " << chosenPort->error();
    }
}

void DataTransmissionHandler::run() {
    qDebug() << "DataTransmissionHandler::run()";

    this->sock = new QUdpSocket(this);
    if (!sock->bind(myAddress, myPort)) {
        qDebug() << "Socket bind error:" << sock->errorString();
    } else {
        qDebug() << "Socket binded to " << myAddress.toString() << "on the port " << myPort;
    }
    sock->open(QIODevice::ReadWrite);
    this->chosenPort = new QSerialPort(this);
    this->connectToComPort();
    this->startDataTransmission();
    this->recieveData();
}

QList<quint16> DataTransmissionHandler::prepareNumbers(QByteArray rawBytes) {
    QList<quint16> numbers = QList<quint16>();

    quint32 i = 0;
    while (i < rawBytes.size()) {
        numbers.push_back(quint16(rawBytes[i] << 8 | rawBytes[i + 1]));
        i += 2;
    }

    //TODO: check if it returns correct and not corrupted when func stack is cleared
    return numbers;
}


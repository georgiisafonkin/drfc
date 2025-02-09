#include "DataTransmissionHandler.h"
#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <vector>

DataTransmissionHandler::DataTransmissionHandler(QObject *parent)
    : QThread{parent}, address(QHostAddress::LocalHost), port(8080)
{
    sock = new QUdpSocket(this);

    if (!sock->bind(address, port)) {
        qDebug() << "Socket bind error:" << sock->errorString();
    } else {
        qDebug() << "Socket binded to " << address.toString() << "on the port " << port;
    }

    elapsedTimer = QElapsedTimer();
}



int *DataTransmissionHandler::createStartMessage() {
    static int message[8];

    // Start message creation
    message[0] = static_cast<int>(1000 * Ng) >> 8;
    message[1] = static_cast<int>(1000 * Ng) & 0xff;

    message[2] = static_cast<int>(1000 * lineLength) >> 8;
    message[3] = static_cast<int>(1000 * lineLength) & 0xff;

    message[4] = static_cast<int>(1000 * lengthUdpPack) >> 8;
    message[5] = static_cast<int>(1000 * lengthUdpPack) & 0xff;

    message[6] = static_cast<int>(1000 * freqSendData) >> 8;
    message[7] = static_cast<int>(1000 * freqSendData) & 0xff;

    return message;
}

void DataTransmissionHandler::startDataTransmission() {
    int* message = createStartMessage();
    sock->writeDatagram(reinterpret_cast<const char*>(message), sizeof(int) * 8, address, cl_port);
    qDebug() << "Start message sent to the card.";
}

void DataTransmissionHandler::recieveData() {
    elapsedTimer.start();
    while (true) {
        QByteArray datagram;
        datagram.resize(lengthUdpPack + 5);  // Adjust size as needed

        // Receive the data from the socket
        qint64 bytesRead = sock->readDatagram(datagram.data(), datagram.size(), &address, &cl_port);

        if (bytesRead > 0) {
            // qDebug() << "Received data:" << datagram;
            processReceivedData(datagram);
        }
        else {
            if (elapsedTimer.elapsed() >= 3000) {
                qDebug() << "Can't receive any packet. Shut down...";
                processReceivedData();
                break;
            }
        }
    }
}

void DataTransmissionHandler::processReceivedData(const QByteArray &data) {
    //parse it to int16 array for chart drawer
     std::vector<qint16> numbers;
     for (int i = 3; i <= data.length() - 1; ++i) {
         numbers.push_back(qint16(data[i] << 8 | data[i + 1]));
    }
    //signal-slot to gui for drawing
    ChartDataReady(index, numbers);

    elapsedTimer.restart();
    static int prevNumPack = 0;
    int numPack = int(data[1] << 8 | data[2]);
    qDebug() << "numPack: " << numPack;
    if (numPack == 0) {
        qDebug() << "numPack == 0.";
        if (index != 0) {
            QString fileName = QString("reflectogram_%1.bin").arg(index);
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << "Couldn't open " << fileName << "for writing.";
            }
            else {
                qDebug() << "Successful open " << fileName << "for writing.";
                QDataStream out(&file);
                out.setByteOrder(QDataStream::BigEndian);
                out.writeRawData(array.data(), array.size());
                file.close();
            }
            array.clear();
        }
        array.insert(array.end(), data.begin(), data.end());
        qDebug() << "Array size: " << array.size() << "data size: " << data.size();
        prevNumPack = numPack;
        index += 1;
    }
    else if (numPack - prevNumPack == 1) {
        prevNumPack = numPack;
        array.insert(array.end(), data.begin(), data.end());
    }
    qDebug() << "Processing received data of size:" << data.size();
}

void DataTransmissionHandler::processReceivedData() {
    QString fileName = QString("reflectogram_%1.bin").arg(index);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Couldn't open " << fileName << "for writing.";
    }
    else {
        qDebug() << "Successful open " << fileName << "for writing.";
        QDataStream out(&file);
        out.setByteOrder(QDataStream::BigEndian);
        out.writeRawData(array.data(), array.size());
        file.close();
    }
    array.clear();
}

void DataTransmissionHandler::run() {
    this->startDataTransmission();
    this->recieveData();
}


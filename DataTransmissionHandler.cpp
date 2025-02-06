#include "DataTransmissionHandler.h"
#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <vector>

DataTransmissionHandler::DataTransmissionHandler(QObject *parent)
    : QObject{parent}, address(QHostAddress::LocalHost), port(8080)
{
    sock = new QUdpSocket(this);

    if (!sock->bind(address, port)) {
        qDebug() << "Socket bind error:" << sock->errorString();
    } else {
        qDebug() << "Socket binded to " << address.toString() << "on the port " << port;
    }

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
    while (true) {
        QByteArray datagram;
        datagram.resize(lengthUdpPack + 5);  // Adjust size as needed

        // Receive the data from the socket
        qint64 bytesRead = sock->readDatagram(datagram.data(), datagram.size(), &address, &cl_port);

        if (bytesRead > 0) {
            qDebug() << "Received data:" << datagram;
            processReceivedData(datagram);
        }
        // else {
        //     qDebug() << "Error receiving data.";
        // }
    }
}

void DataTransmissionHandler::processReceivedData(const QByteArray &data) {
    std::vector<char> array;
    static int index = 0;
    static int prevNumPack = 0;
    int numPack = int(data[1] << 8 | data[2]);
    qDebug() << "numPack: " << numPack;
    if (numPack == 0) {
        qDebug() << "numPack == 0.";
        if (index != 0) {
            QString fileName = QString("reflectogram_%1.bin").arg(index);
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
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
        array.insert(array.begin(), data.begin(), data.end());
        prevNumPack = numPack;
        index += 1;
    }
    else if (numPack - prevNumPack == 1) {
        qDebug() << "numPack - prevNumPack == 1";
        prevNumPack = numPack;
        array.insert(array.end(), data.begin(), data.end());
    }
    qDebug() << "Processing received data of size:" << data.size();
}

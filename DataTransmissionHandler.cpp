#include "DataTransmissionHandler.h"
#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <vector>
#include <QProcess>
#include <QNetworkDatagram>

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
    // message[0] = static_cast<qint16>(1000 * Ng) >> 8;
    // message[1] = static_cast<qint16>(1000 * Ng) & 0xff;

    message.append(static_cast<qint16>(lineLength) >> 8);
    message.append(static_cast<qint16>(lineLength) & 0xff);
    // message[2] = static_cast<qint16>(lineLength) >> 8;
    // message[3] = static_cast<qint16>(lineLength) & 0xff;

    message.append(static_cast<qint16>(lengthUdpPack) >> 8);
    message.append(static_cast<qint16>(lengthUdpPack) & 0xff);
    // message[4] = static_cast<qint16>(lengthUdpPack) >> 8;
    // message[5] = static_cast<qint16>(lengthUdpPack) & 0xff;

    message.append(static_cast<qint16>(freqSendData) >> 8);
    message.append(static_cast<qint16>(freqSendData) & 0xff);
    // message[6] = static_cast<qint16>(freqSendData) >> 8;
    // message[7] = static_cast<qint16>(freqSendData) & 0xff;

    message.append(static_cast<qint16>(pulseWidth) >> 8);
    message.append(static_cast<qint16>(pulseWidth) & 0xff);
    // message[8] = static_cast<qint16>(pulseWidth) >> 8;
    // message[9] = static_cast<qint16>(pulseWidth) & 0xff;

    return message;
}

void DataTransmissionHandler::startDataTransmission() {
    QByteArray message = createStartMessage();
    sock->writeDatagram(message, message.size(), clAddress, clPort);
    qDebug() << "Start message sent to the card.";
}

void DataTransmissionHandler::recieveData() {
    // qDebug() << "Recieved from port: " << chosenPort->readAll();
    elapsedTimer.start();
    while (true) {
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
        // qint64 bytesRead = sock->readDatagram(datagram.data(), datagram.size(), &clAddress, &clPort);
        if (networkDatagram.data().size() > 0) {
            qDebug() << "Received data:" << networkDatagram.data();
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

void DataTransmissionHandler::setStaticIP() {
    QProcess process;
    QString command = "netsh interface ip set address \"Ethernet\" static 192.168.1.42 255.255.255.0 192.168.1.1";
    process.start("cmd.exe", {"/c", command});
    process.waitForFinished();

    QString error = process.readAllStandardError();

    if (!error.isEmpty()) {
        // QMessageBox::critical(this, "Error", "Failed to set static IP: " + error);
    } else {
        // QMessageBox::information(this, "Success", "Static IP successfully set to 192.168.1.42");
    }
}

void DataTransmissionHandler::connectToComPort() {
    qDebug() << "DataTransmissionHandler::connectToComPort()";

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


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

    message.append(static_cast<qint16>(1000 * Ng) >> 8);
    message.append(static_cast<qint16>(1000 * Ng) & 0xff);

    message.append(static_cast<qint16>(lineLength) >> 8);
    message.append(static_cast<qint16>(lineLength) & 0xff);

    message.append(static_cast<qint16>(lengthUdpPack) >> 8);
    message.append(static_cast<qint16>(lengthUdpPack) & 0xff);

    message.append(static_cast<qint16>(pulseFreq) >> 8);
    message.append(static_cast<qint16>(pulseFreq) & 0xff);

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
        QNetworkDatagram networkDatagram;
        networkDatagram = sock->receiveDatagram(lengthUdpPack + 5);
        if (networkDatagram.data().size() > 0) {
            qDebug() << "Received data size: " << networkDatagram.data().size();
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

void DataTransmissionHandler::setLineLength(int newLineLength)
{
    lineLength = newLineLength;
}

void DataTransmissionHandler::setPulseFreq(int newFreqSendData)
{
    pulseFreq = newFreqSendData;
}

void DataTransmissionHandler::setPulseWidth(int newPulseWidth)
{
    pulseWidth = newPulseWidth;
}

int DataTransmissionHandler::getLineLength() const
{
    return lineLength;
}

int DataTransmissionHandler::getPulseFreq() const
{
    return pulseFreq;
}

int DataTransmissionHandler::getPulseWidth() const
{
    return pulseWidth;
}

void DataTransmissionHandler::processReceivedData(const QByteArray &data) {
    elapsedTimer.restart();
    static int prevNumPack = 0;
    int numPack = int(data[1] << 8 | data[2]);
    if (numPack == 0) {
        if (index != 0) {
            QPair<qint16, QByteArray>* newPair = new QPair<qint16, QByteArray>(index, *array);
            emit ReflectogramDataReady(*newPair); //сигналим FileWriter, что очередная рефлектограмма готова для записи в файл
            emit ChartDataReady(prepareNumbers(*array)); //сигналим GUI, что данные для отрисовки готовы

            array->clear();
        }
        array->append(data.begin() + 5, data.size() - 5);
        prevNumPack = numPack;
        index += 1;
    }
    else if (numPack - prevNumPack == 1) {
        prevNumPack = numPack;
        array->append(data.begin() + 5, data.size() - 5);
    }
}

// функция ниже написана для случая когда новые данные перестают приходить и срабатывает elapsedTimer
void DataTransmissionHandler::processReceivedData() {
    ReflectogramDataReady(QPair<qint16, QByteArray>(index, *array));
    ChartDataReady(prepareNumbers(*array));
    array->clear();
}

void DataTransmissionHandler::connectToComPort() {
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

//функция ниже переводит сырые байты рефлектограммы в список двубайтных целочисленных значений для отрисовки
QList<qint16> DataTransmissionHandler::prepareNumbers(QByteArray rawBytes) {
    QList<qint16> numbers = QList<qint16>();

    quint32 i = 0;
    while (i < rawBytes.size() - 1) {
        qint16 highByte = static_cast<qint8>(rawBytes[i]);
        qint16 lowByte = static_cast<qint8>(rawBytes[i + 1]);

        qint16 number = (highByte << 8) | lowByte; // Big-endian порядок
        numbers.push_back(number);

        i += 2;
    }
    return numbers;
}


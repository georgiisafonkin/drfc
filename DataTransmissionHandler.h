#ifndef DATATRANSMISSIONHANDLER_H
#define DATATRANSMISSIONHANDLER_H

#include <QObject>
#include <QElapsedTimer>
#include <qudpsocket.h>
class DataTransmissionHandler : public QObject
{
    Q_OBJECT
public:
    explicit DataTransmissionHandler(QObject *parent = nullptr);
    DataTransmissionHandler(const QHostAddress& address, quint16 port);
    void startDataTransmission();
    void recieveData();
private:
    float Ng = 1.46;
    int lineLength = 5000;
    int lengthUdpPack = 1024;
    int freqSendData = 100;
    QUdpSocket* sock;
    QHostAddress address;
    quint16 port;
    quint16 cl_port = 7070;
    std::vector<char> array;
    int* createStartMessage();
    void processReceivedData(const QByteArray &data);
    void processReceivedData();
    void finishTransmission();
    int index = 0;
    QElapsedTimer elapsedTimer;
signals:
};

#endif // DATATRANSMISSIONHANDLER_H

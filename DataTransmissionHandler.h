#ifndef DATATRANSMISSIONHANDLER_H
#define DATATRANSMISSIONHANDLER_H

#include <QObject>
#include <QElapsedTimer>
#include <qudpsocket.h>
#include <QThread>
#include <QSerialPort>
class DataTransmissionHandler : public QThread
{
    Q_OBJECT
public:
    explicit DataTransmissionHandler(QObject *parent = nullptr);
    DataTransmissionHandler(const QHostAddress& address, quint16 port);
    void startDataTransmission();
    void recieveData();
    void setComPortName(const QString &newComPortName);

private:
    //constants for start message
    float Ng = 1.46;
    int lineLength = 5000;
    int lengthUdpPack = 1024;
    int freqSendData = 100;
    int pulseWidth = 10;

    //for connection
    QUdpSocket* sock;
    QHostAddress myAddress = QHostAddress("192.168.1.42");
    QHostAddress clAddress = QHostAddress("192.168.1.10");
    quint16 myPort = 8080;
    quint16 clPort = 8080;
    QString comPortName;
    QSerialPort* chosenPort;
    void setStaticIP();
    void connectToComPort();

    std::vector<char> array;
    QByteArray createStartMessage();
    void processReceivedData(const QByteArray &data);
    void processReceivedData();
    void finishTransmission();
    int index = 0;
    QElapsedTimer elapsedTimer;
protected:
    void run() override;
signals:
    void ChartDataReady(int index, const std::vector<qint16>& numbers);
};

#endif // DATATRANSMISSIONHANDLER_H

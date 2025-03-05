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

    void setLineLength(int newLineLength);

    void setFreqSendData(int newFreqSendData);

    void setPulseWidth(int newPulseWidth);

private:
    //constants for start message
    float Ng = 1.46;
    int lineLength = 5000;
    int lengthUdpPack = 5000;
    int freqSendData = 100;
    int pulseWidth = 100;

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

    QByteArray* array = new QByteArray();
    QByteArray createStartMessage();
    void processReceivedData(const QByteArray &data);
    void processReceivedData();
    void finishTransmission();
    quint16 index = 0;
    QElapsedTimer elapsedTimer;

    QList<qint16> prepareNumbers(QByteArray rawBytes);
protected:
    void run() override;
signals:
    void ReflectogramDataReady(const QPair<qint16, QByteArray>& newPair);
    void ChartDataReady(const QList<qint16>& numbers);
};

#endif // DATATRANSMISSIONHANDLER_H

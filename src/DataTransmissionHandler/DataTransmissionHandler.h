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
    void setPulseFreq(int newFreqSendData);
    void setPulseWidth(int newPulseWidth);

    int getLineLength() const;
    int getPulseFreq() const;
    int getPulseWidth() const;

private:
    //constants for start message (card parameters)
    float Ng = 1.46;
    int lineLength = 5000;
    int lengthUdpPack = 1024;
    int pulseFreq = 100;
    int pulseWidth = 100;

    //for connection
    QUdpSocket* sock;
    QHostAddress myAddress = QHostAddress("192.168.1.42");
    QHostAddress clAddress = QHostAddress("192.168.1.10");
    quint16 myPort = 8080;
    quint16 clPort = 8080;
    QString comPortName;
    QSerialPort* chosenPort;

    //
    //ВАЖНО!
    // void setStaticIP();
    // Статический АйПи я выставлял вручную внутри ОС.
    // Чтобы это происходило автоматически,
    // необходимо реализовать эту функцию.
    // Когда будешь тестировать программу на своём ПК настрой сначала статический АйПи
    // на соответствующем ethernet-интерфейсе, либо реализуй эту функцию.
    //

    void connectToComPort();

    QByteArray* array = new QByteArray(); //массив для рефлектограммы
    QByteArray createStartMessage();
    void processReceivedData(const QByteArray &data);
    void processReceivedData();
    void finishTransmission();
    quint16 index = 0;
    QElapsedTimer elapsedTimer; //таймер на случай, если новые данные перестанут приходить

    QList<qint16> prepareNumbers(QByteArray rawBytes);
protected:
    void run() override;
signals:
    void ReflectogramDataReady(const QPair<qint16, QByteArray>& newPair);
    void ChartDataReady(const QList<qint16>& numbers);
};

#endif // DATATRANSMISSIONHANDLER_H

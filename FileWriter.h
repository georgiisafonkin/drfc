#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QMutex>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <QWaitCondition>

class FileWriter : public QThread
{
public:
    explicit FileWriter(QObject *parent = nullptr);
    void updateReflectogramData(QPair<quint16, QByteArray>);
    QWaitCondition* queueNotEmpty;
private:
    QQueue<QPair<quint16, QByteArray>>* writeQueue;
    QMutex* queueMutex;
    void writeData();
protected:
    void run() override;
};

#endif // FILEWRITER_H

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QQueue>
#include <QThread>

class FileWriter : public QThread
{
public:
    explicit FileWriter(QObject *parent = nullptr);
    void updateReflectogramData(QPair<quint16, QByteArray>);
private:
    QQueue<QPair<quint16, QByteArray>>* writeQueue;
    void writeData();
protected:
    void run() override;
};

#endif // FILEWRITER_H

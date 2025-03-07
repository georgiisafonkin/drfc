#include "FileWriter.h"

#include <QDataStream>
#include <QFile>
#include <qdebug.h>

//
// ВАЖНО!!!
// Я не уверен, что FileWriter нужны примитивы синхронизации при записи данных в файлы.
// Дело в том, что в текущей версии программы у нас один экземпляр этого класса
// пишет в файл, т.е. разделяемого ресурса нет как такового .
// Однако, если в будущем захочешь сделать, чтобы сразу несколько потоков работали с файлами
// использование мьютекса может оказаться необходимым. Поэтому решил оставить
//

FileWriter::FileWriter(QObject *parent)
    : QThread{parent}, writeQueue(new QQueue<QPair<qint16, QByteArray>>()),
    queueMutex(new QMutex), queueNotEmpty(new QWaitCondition())
{
}

void FileWriter::writeData() {
    while (!QThread::currentThread()->isInterruptionRequested()) {
        QMutexLocker locker(queueMutex);

        while (writeQueue->empty()) {
            if (QThread::currentThread()->isInterruptionRequested()) {
                return;  // Exit thread safely
            }
            queueNotEmpty->wait(queueMutex);  // Wait until new data is available
        }

        if (!writeQueue->empty()) {
            QPair queuePair = writeQueue->dequeue();

            locker.unlock();

            qint16 index = queuePair.first;
            QByteArray reflectogram = queuePair.second;

            QString fileName = QString("reflectogram_%1.bin").arg(index);
            QFile file(fileName);

            if (!file.open(QIODevice::WriteOnly)) {
            } else {
                QDataStream out(&file);
                out.setByteOrder(QDataStream::BigEndian);
                out.writeRawData(reflectogram.data(), reflectogram.size());
                file.close();
            }
            locker.relock();
        }
    }
}

void FileWriter::updateReflectogramData(QPair<qint16, QByteArray> newPair) {
    QMutexLocker locker(queueMutex);
    writeQueue->enqueue(newPair);
    queueNotEmpty->wakeOne();
}

void FileWriter::run() {
    writeData();
}

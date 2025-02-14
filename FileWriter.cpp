#include "FileWriter.h"

#include <QDataStream>
#include <QFile>
#include <qdebug.h>

FileWriter::FileWriter(QObject *parent)
    : QThread{parent}, writeQueue(new QQueue<QPair<quint16, QByteArray>>()),
    queueMutex(new QMutex), queueNotEmpty(new QWaitCondition())
{
    qDebug() << "FileWriter object was created in Thread with TID: " << QThread::currentThreadId();
}

void FileWriter::writeData() {
    qDebug() << "FileWriter::writeData() was invoked by thread with TID: " << QThread::currentThreadId();
    while (!QThread::currentThread()->isInterruptionRequested()) {
        qDebug() << "FileWriter::writeData() enterd loop by thread with TID: " << QThread::currentThreadId();
        QMutexLocker locker(queueMutex);

        while (writeQueue->empty()) {
            qDebug() << "empty writeQueue in thread with TID: " << QThread::currentThreadId();
            if (QThread::currentThread()->isInterruptionRequested()) {
                return;  // Exit thread safely
            }
            queueNotEmpty->wait(queueMutex);  // Wait until new data is available
        }

        if (!writeQueue->empty()) {
            qDebug() << "NOT empty writeQueue in thread with TID: " << QThread::currentThreadId();
            QPair queuePair = writeQueue->dequeue();

            locker.unlock();

            quint16 index = queuePair.first;
            QByteArray reflectogram = queuePair.second;

            QString fileName = QString("reflectogram_%1.bin").arg(index);
            QFile file(fileName);

            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << "Couldn't open " << fileName << "for writing.";
            } else {
                QDataStream out(&file);
                out.setByteOrder(QDataStream::BigEndian);
                out.writeRawData(reflectogram.data(), reflectogram.size());
                file.close();
                // qDebug() << "Reflectogram to write: " << reflectogram.data();
                // qDebug() << "wrote to file " << fileName << ".";
            }
            locker.relock();
        }
    }
}

void FileWriter::updateReflectogramData(QPair<quint16, QByteArray> newPair) {
    qDebug() << "FileWriter::updateReflectogramDatainvoked in Thread with TID: " << QThread::currentThreadId();
    QMutexLocker locker(queueMutex);
    writeQueue->enqueue(newPair);
    queueNotEmpty->wakeOne();
}

void FileWriter::run() {
    qDebug() << "FileWriter::run() invoked in Thread with TID: " << QThread::currentThreadId();
    writeData();
}

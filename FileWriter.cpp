#include "FileWriter.h"

#include <QDataStream>
#include <QFile>
#include <qdebug.h>

FileWriter::FileWriter(QObject *parent)
    : QThread{parent}
{
    writeQueue = new QQueue<QPair<quint16, QByteArray>>();
}

void FileWriter::writeData() {
    qDebug() << "FileWriter::writeData()";
    while (!QThread::currentThread()->isInterruptionRequested()) {
        qDebug() << "FileWriter::writeData() in loop";
        if (!writeQueue->empty()) {
            QPair queuePair = writeQueue->dequeue();

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
                qDebug() << "Reflectogram to write: " << reflectogram.data();
                qDebug() << "wrote to file " << fileName << ".";
            }
        } else {
            QThread::msleep(1000);
        }
    }
}

void FileWriter::updateReflectogramData(QPair<quint16, QByteArray> newPair) {
    qDebug() << "FileWriter::updateReflectogramData";
    writeQueue->enqueue(newPair);
}

void FileWriter::run() {
    qDebug() << "FileWriter::run()";
    writeData();
}

//TODO: connect signal-slot

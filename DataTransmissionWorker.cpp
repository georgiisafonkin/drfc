#include "DataTransmissionWorker.h"

DataTransmissionWorker::DataTransmissionWorker(QObject *parent)
    : QThread{parent}
{
    dth = new DataTransmissionHandler();
}

void DataTransmissionWorker::run() {
    dth->startDataTransmission();
    dth->recieveData();
}

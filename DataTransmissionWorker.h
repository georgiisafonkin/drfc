#ifndef DATATRANSMISSIONWORKER_H
#define DATATRANSMISSIONWORKER_H

#include "DataTransmissionHandler.h"

#include <QThread>

class DataTransmissionWorker : public QThread
{
public:
    explicit DataTransmissionWorker(QObject *parent = nullptr);
private:
    DataTransmissionHandler* dth;
protected:
    void run() override;
};

#endif // DATATRANSMISSIONWORKER_H

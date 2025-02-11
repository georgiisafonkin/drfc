#include "gui.h"
#include <QAbstractSocket>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<std::vector<qint16>>("std::vector<qint16>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    GUI gui;
    gui.setWindowTitle("drfc");
    gui.resize(400, 200);
    gui.show();

    // DataTransmissionHandler* dth = new DataTransmissionHandler();
    // dth->startDataTransmission();
    // dth->recieveData();

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}

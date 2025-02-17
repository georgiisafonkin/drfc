#include "gui.h"
#include <QAbstractSocket>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<QList<qint16>>("std::vector<qint16>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QPair<quint16, QByteArray>>("QPair<quint16, QByteArray>");

    GUI gui;
    gui.setWindowTitle("drfc");
    gui.resize(400, 200);
    gui.show();

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

//TODO: fix charts (now plot wrong)
//TODO: fix (after termination of GUI thread other threads must be terminated too)
//TODO: fix (GUI Thread must work smoothly without freezes, now it's not)

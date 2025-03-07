#include "GUI/gui.h"
#include "LoopedList/LoopedList.h"
#include "mainWindowDAS/mainWindowDAS.h"
#include <QAbstractSocket>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Qt version: " << QT_VERSION_STR;


    //честно хз что это, но как я понял мы должны "зарегестрировать" сложные типы, используемые для межпоточного взаимодействия
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QPair<qint16, QByteArray>>("QPair<qint16, QByteArray>");

    GUI gui;
    gui.setWindowTitle("drfc");
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

// Общий план
// 1. Отрисовка рефлектограмм в реальном времени done
// 2. Отрисовка водопада по рефлектограммам в реальном времени
// 3. Кнопки "Старт", "Стоп" work in progress
// 4. Возможность задавать частоту импульса через GUI done
// 5. Возможность задавать длину линии через GUI done
// 6. Возможность задавать ширину импульса через GUI done
// 7. Поле с галочкой, если нужно сохранять рефлектограммы в файлы work in progress
// 8. Изменить наименование сохраняемых данных по следующему формату:
// Refl_№_YYYY-MM-DD-hh-mm-ss-millisecs_freq_len

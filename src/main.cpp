#include "GUI/gui.h"
#include "mainWindowDAS/mainWindowDAS.h"
#include <QAbstractSocket>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<QList<qint16>>("std::vector<qint16>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QPair<qint16, QByteArray>>("QPair<qint16, QByteArray>");


    GUI gui;
    gui.setWindowTitle("drfc");
    gui.show();

    // QMainWindow* uiMainWindow = new QMainWindow();
    // Ui::MainWindow DASUi;
    // DASUi.setupUi(uiMainWindow);
    // uiMainWindow->show();

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

//TODO: find out the reason for the jumps when drawing charts
//TODO: 24 or 30 FPS

//Packets may be lost???!!!??

//TODO: посмотреть по ethernet-трафику сколько приходит пакетов, то что ничего не теряется
//Осталось проверить с генератором. На плате без генератора потерь нет


//TODO: интегрировать designer в проект, чтоб нормально UI делать

//План до пятницы
// Водопад
// Фикс. масштаб графика
// Масштабирование главного окна


// Общий план
// 1. Отрисовка рефлектограмм в реальном времени
// 2. Отрисовка водопада по рефлектограммам в реальном времени
// 3. Кнопки "Старт", "Стоп"
// 4. Возможность задавать частоту импульса через GUI
// 5. Возможность задавать длину линии через GUI
// 6. Возможность задавать ширину импульса через GUI
// 7. Поле с галочкой, если нужно сохранять рефлектограммы в файлы
// 8. Изменить наименование сохраняемых данных по следующему формату:
// Refl_№_YYYY-MM-DD-hh-mm-ss-millisecs_freq_len

#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QMessageBox>
#include <QObject>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QWidget* parent = nullptr);
private:
    void showAboutDialog() {
        QMessageBox::information(nullptr, "О программе", "Разработано в лаборатории сенсорики ПИШ НГУ.\n2025г.");
    }
};

#endif // MENUBAR_H

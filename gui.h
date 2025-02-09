#ifndef GUI_H
#define GUI_H

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class GUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit GUI(QWidget *parent = nullptr);

private:
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QLabel* label;
    QComboBox* comPortCombo;
    QPushButton* refreshButton;
    QPushButton* selectButton;
    void refreshComPorts();
    void selectComPort();
signals:
};

#endif // GUI_H

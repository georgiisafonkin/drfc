/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWDAS_H
#define MAINWINDOWDAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *mainVL;
    QHBoxLayout *optionsHL;
    QVBoxLayout *comPortStartStopVL;
    QVBoxLayout *comPortOptionsVL;
    QLabel *choseComPortLabel;
    QComboBox *comPortsComboBox;
    QPushButton *refreshPortsButton;
    QPushButton *choosePortButtom;
    QHBoxLayout *startStopHL;
    QPushButton *startButton;
    QPushButton *stopButton;
    QVBoxLayout *parametersVL;
    QLabel *label;
    QCheckBox *saveCheckBox;
    QHBoxLayout *lineLengthHL;
    QLabel *lineLengthLabel;
    QLineEdit *lineLengthLE;
    QHBoxLayout *pulseFreqHL;
    QLabel *pulseFreqLabel;
    QLineEdit *pulseFreqLE;
    QHBoxLayout *pulseWidthHL;
    QLabel *pulseWidthLabel;
    QLineEdit *pulseWidthLE;
    QHBoxLayout *GraphicsHL;
    QVBoxLayout *ReflVL;
    QGraphicsView *reflGV;
    QLabel *reflLabel;
    QMenuBar *menuBar;
    QMenu *systemMenu;
    QMenu *aboutMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mainVL = new QVBoxLayout();
        mainVL->setObjectName(QString::fromUtf8("mainVL"));
        optionsHL = new QHBoxLayout();
        optionsHL->setObjectName(QString::fromUtf8("optionsHL"));
        comPortStartStopVL = new QVBoxLayout();
        comPortStartStopVL->setObjectName(QString::fromUtf8("comPortStartStopVL"));
        comPortOptionsVL = new QVBoxLayout();
        comPortOptionsVL->setObjectName(QString::fromUtf8("comPortOptionsVL"));
        choseComPortLabel = new QLabel(centralwidget);
        choseComPortLabel->setObjectName(QString::fromUtf8("choseComPortLabel"));

        comPortOptionsVL->addWidget(choseComPortLabel);

        comPortsComboBox = new QComboBox(centralwidget);
        comPortsComboBox->setObjectName(QString::fromUtf8("comPortsComboBox"));

        comPortOptionsVL->addWidget(comPortsComboBox);

        refreshPortsButton = new QPushButton(centralwidget);
        refreshPortsButton->setObjectName(QString::fromUtf8("refreshPortsButton"));

        comPortOptionsVL->addWidget(refreshPortsButton);

        choosePortButtom = new QPushButton(centralwidget);
        choosePortButtom->setObjectName(QString::fromUtf8("choosePortButtom"));

        comPortOptionsVL->addWidget(choosePortButtom);


        comPortStartStopVL->addLayout(comPortOptionsVL);

        startStopHL = new QHBoxLayout();
        startStopHL->setObjectName(QString::fromUtf8("startStopHL"));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        startStopHL->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        startStopHL->addWidget(stopButton);


        comPortStartStopVL->addLayout(startStopHL);


        optionsHL->addLayout(comPortStartStopVL);

        parametersVL = new QVBoxLayout();
        parametersVL->setObjectName(QString::fromUtf8("parametersVL"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        parametersVL->addWidget(label);

        saveCheckBox = new QCheckBox(centralwidget);
        saveCheckBox->setObjectName(QString::fromUtf8("saveCheckBox"));

        parametersVL->addWidget(saveCheckBox);

        lineLengthHL = new QHBoxLayout();
        lineLengthHL->setObjectName(QString::fromUtf8("lineLengthHL"));
        lineLengthLabel = new QLabel(centralwidget);
        lineLengthLabel->setObjectName(QString::fromUtf8("lineLengthLabel"));

        lineLengthHL->addWidget(lineLengthLabel);

        lineLengthLE = new QLineEdit(centralwidget);
        lineLengthLE->setObjectName(QString::fromUtf8("lineLengthLE"));

        lineLengthHL->addWidget(lineLengthLE);


        parametersVL->addLayout(lineLengthHL);

        pulseFreqHL = new QHBoxLayout();
        pulseFreqHL->setObjectName(QString::fromUtf8("pulseFreqHL"));
        pulseFreqLabel = new QLabel(centralwidget);
        pulseFreqLabel->setObjectName(QString::fromUtf8("pulseFreqLabel"));

        pulseFreqHL->addWidget(pulseFreqLabel);

        pulseFreqLE = new QLineEdit(centralwidget);
        pulseFreqLE->setObjectName(QString::fromUtf8("pulseFreqLE"));

        pulseFreqHL->addWidget(pulseFreqLE);


        parametersVL->addLayout(pulseFreqHL);

        pulseWidthHL = new QHBoxLayout();
        pulseWidthHL->setObjectName(QString::fromUtf8("pulseWidthHL"));
        pulseWidthLabel = new QLabel(centralwidget);
        pulseWidthLabel->setObjectName(QString::fromUtf8("pulseWidthLabel"));

        pulseWidthHL->addWidget(pulseWidthLabel);

        pulseWidthLE = new QLineEdit(centralwidget);
        pulseWidthLE->setObjectName(QString::fromUtf8("pulseWidthLE"));

        pulseWidthHL->addWidget(pulseWidthLE);


        parametersVL->addLayout(pulseWidthHL);


        optionsHL->addLayout(parametersVL);


        mainVL->addLayout(optionsHL);

        GraphicsHL = new QHBoxLayout();
        GraphicsHL->setObjectName(QString::fromUtf8("GraphicsHL"));
        ReflVL = new QVBoxLayout();
        ReflVL->setObjectName(QString::fromUtf8("ReflVL"));
        reflGV = new QGraphicsView(centralwidget);
        reflGV->setObjectName(QString::fromUtf8("reflGV"));

        ReflVL->addWidget(reflGV);

        reflLabel = new QLabel(centralwidget);
        reflLabel->setObjectName(QString::fromUtf8("reflLabel"));

        ReflVL->addWidget(reflLabel);


        GraphicsHL->addLayout(ReflVL);


        mainVL->addLayout(GraphicsHL);


        verticalLayout->addLayout(mainVL);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        systemMenu = new QMenu(menuBar);
        systemMenu->setObjectName(QString::fromUtf8("systemMenu"));
        aboutMenu = new QMenu(menuBar);
        aboutMenu->setObjectName(QString::fromUtf8("aboutMenu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(systemMenu->menuAction());
        menuBar->addAction(aboutMenu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        choseComPortLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 COM-\320\277\320\276\321\200\321\202:", nullptr));
        refreshPortsButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        choosePortButtom->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        saveCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273\321\213", nullptr));
        lineLengthLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\273\320\270\320\275\320\260 \320\273\320\270\320\275\320\270\320\270", nullptr));
        pulseFreqLabel->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\270\320\274\320\277\321\203\320\273\321\214\321\201\320\276\320\262", nullptr));
        pulseWidthLabel->setText(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\200\320\270\320\275\320\260 \320\270\320\274\320\277\321\203\320\273\321\214\321\201\320\260", nullptr));
        reflLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\321\204\320\273\320\265\320\272\321\202\320\276\320\263\321\200\320\260\320\274\320\274\320\260", nullptr));
        systemMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
        aboutMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

    void setReflGV(QGraphicsView *newReflGV);
};

inline void Ui_MainWindow::setReflGV(QGraphicsView *newReflGV)
{
    if (reflGV) {
        delete reflGV;
    }

    reflGV = newReflGV;
    ReflVL->insertWidget(0, reflGV);
}

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWDAS_H

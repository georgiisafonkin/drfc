#include "MenuBar.h"

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent) {
    QMenu* systemMenu = addMenu("Система");

    QAction* exitAction = new QAction("Выход", this);
    systemMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, parent, &QWidget::close);

    QMenu* helpMenu = addMenu("Справка");
    QAction* aboutAction = new QAction("О программе", this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MenuBar::showAboutDialog);
}



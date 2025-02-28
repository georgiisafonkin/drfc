#include "LabeledLineEdit.h"

LabeledLineEdit::LabeledLineEdit(QWidget *parent)
    : QWidget{parent}, label{new QLabel(this)},
    lineEdit{new QLineEdit(this)}, layout{new QFormLayout()}
{
    // lineEdit->setFixedHeight(20);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    // layout->setSpacing(0);
    // layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
}

LabeledLineEdit::LabeledLineEdit(QWidget *parent, QString text) : LabeledLineEdit(parent) {
    label->setText(text);
}

QLineEdit *LabeledLineEdit::getLineEdit() const
{
    return lineEdit;
}

QLabel *LabeledLineEdit::getLabel() const
{
    return label;
}

QFormLayout *LabeledLineEdit::getLayout() const
{
    return layout;
}

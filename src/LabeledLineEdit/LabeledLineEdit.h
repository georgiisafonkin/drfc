#ifndef LABELEDLINEEDIT_H
#define LABELEDLINEEDIT_H

#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>

class LabeledLineEdit : public QWidget
{
    Q_OBJECT
public:
    explicit LabeledLineEdit(QWidget *parent = nullptr);
    LabeledLineEdit(QWidget *parent, QString text);
    QLineEdit *getLineEdit() const;
    QLabel *getLabel() const;
    QFormLayout *getLayout() const;

private:
    QLabel* label;
    QLineEdit* lineEdit;
    QFormLayout* layout;

signals:
};

#endif // LABELEDLINEEDIT_H

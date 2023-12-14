#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include "parser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
//    QVector<QVBoxLayout> left_b, right_b;
//    QVector<QPushButton> left_buttons1, left_buttons2, right_buttons1, right_buttons2;
//    QVector<QLineEdit> edits;
};
#endif // WIDGET_H

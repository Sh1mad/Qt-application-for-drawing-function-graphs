#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include "parser.h"
#include "integral.h"

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

    void plot();

    void on_deleteBut_clicked();

    void on_integralBut_clicked();

    void clear_data();

    void show_integral();

    void hide_integral();

    void set_default_range();

private:
    Ui::Widget *ui;
    QVector<double> x_mas, y_mas;
    tokens tok;
    std::string function;
//    QVector<QVBoxLayout> left_b, right_b;
//    QVector<QPushButton> left_buttons1, left_buttons2, right_buttons1, right_buttons2;
//    QVector<QLineEdit> edits;
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include "parser.h"
#include "integral.h"
#include <QTextEdit>
#include <iostream>
#include <fstream>
#include "QScrollArea"
#include <QErrorMessage>

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
    void on_buildButton_clicked();

    void plot1();

    void plot_int();

    void plot_roots();

    void on_deleteBut_clicked();

    void on_integralBut_clicked();

    void clear_data();

    void show_integral();

    void hide_integral();

    void set_default_range();

    void set_data(QVector<double> &x_mas, QVector<double> &y_mas, double x_min = -100.0, double x_max = 100.0);

    void paint_integral(double a, double b);

    void clear_int();

    void clear_roots();

    void on_root_but_clicked();

    void on_help_but_clicked();

    void init_help();

    void clear_canva();

private:
    Ui::Widget *ui;
    QVector<double> x_mas, y_mas, x_int, y_int, x_root, y_root;
    QTextEdit* help_window = new QTextEdit();
    QString help_str;
    tokens tok;
    std::string function;
    double func_min, func_max;
    QScrollArea* scroll_help = new QScrollArea();
    QErrorMessage errorMessage;
//    QVector<QVBoxLayout> left_b, right_b;
//    QVector<QPushButton> left_buttons1, left_buttons2, right_buttons1, right_buttons2;
//    QVector<QLineEdit> edits;
};
#endif // WIDGET_H

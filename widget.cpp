#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->canva->setInteraction(QCP::iRangeDrag, true);
    ui->canva->setInteraction(QCP::iRangeZoom, true);
    ui->canva->axisRect()->setRangeZoomFactor(0.9);

    ui->canva->addGraph();

    set_default_range();

    ui->canva->xAxis->grid()->setSubGridVisible(true);
    ui->canva->yAxis->grid()->setSubGridVisible(true);

    hide_integral();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::set_default_range(){
    double w_canva = 10.0, h_canva;

    h_canva = static_cast <double>(ui->canva->geometry().size().height()) / static_cast <double>(ui->canva->geometry().size().width()) * w_canva;
    ui->canva->xAxis->setRange(-w_canva, w_canva);
    ui->canva->yAxis->setRange(-h_canva, h_canva);
}

void Widget::on_pushButton_clicked()
{
    clear_data();

    set_default_range();

    function = ui->lineEdit->text().toStdString();

    ConvertToPostfix(function, tok);

    for (int i=0; i<1000001; ++i)
    {
        x_mas << i/10.0 - 50000;
        y_mas << ResultExpr(tok, x_mas.back());
    }
    ui->canva->graph(0)->setData(x_mas, y_mas);

    ui->canva->xAxis->setLabel("x");
    ui->canva->yAxis->setLabel("y");

    ui->canva->replot();

    show_integral();
}

void set_data(QVector<double> &x_mas, QVector<double> &y_mas, double x_min, double x_max){
    for (int i=0; i<1000001; ++i)
    {
        x_mas << i/10.0 - 50000;
        y_mas << ResultExpr(tok, x_mas.back());
    }
}

void Widget::plot(){
    ui->canva->graph(0)->setData(x_mas, y_mas);
    ui->canva->replot();
    ui->canva->update();
}

void Widget::clear_data(){
    x_mas.clear();
    y_mas.clear();
}

void Widget::show_integral(){
    ui->findIntLabel->show();
    ui->fromLabel->show();
    ui->toLabel->show();
    ui->integral_a->show();
    ui->integral_b->show();
    ui->integralBut->show();
    ui->integralLabel->show();
}

void Widget::hide_integral(){
    ui->findIntLabel->hide();
    ui->fromLabel->hide();
    ui->toLabel->hide();
    ui->integral_a->hide();
    ui->integral_b->hide();
    ui->integralBut->hide();
    ui->integralLabel->hide();
}

void Widget::on_deleteBut_clicked()
{
    clear_data();
    plot();
    hide_integral();
}


void Widget::on_integralBut_clicked()
{
    double a,b;
    double res;
    a = ui->integral_a->text().toDouble();
    b = ui->integral_b->text().toDouble();

    res = integral(tok, a, b);
    if (res < 0.001) res = 0;

    if (ui->integral_a->text() == "" || ui->integral_b->text() == "") ui->integralLabel->setText("Введите промежутки интегрирования!");
    else if (a > b) ui->integralLabel->setText("Введите a<b интегрирования!");
    else ui->integralLabel->setText("Интеграл равен: " + QString::number(res));
}


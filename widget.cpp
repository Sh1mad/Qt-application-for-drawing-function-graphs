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
    ui->canva->xAxis->setLabel("x");
    ui->canva->yAxis->setLabel("y");

    ui->canva->addGraph();
    ui->canva->addGraph();
    ui->canva->addGraph();

    set_default_range();

    ui->canva->xAxis->grid()->setSubGridVisible(true);
    ui->canva->yAxis->grid()->setSubGridVisible(true);

    init_help();
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

void Widget::on_buildButton_clicked()
{
    clear_canva();
    set_default_range();

    function = ui->lineEdit->text().toStdString();

    if (function == "") ui->lineEdit->setText("Введите функцию");
    else {
    ConvertToPostfix(function, tok);

    (ui->from_func->text() == "")?(func_min = -100):(func_min = ui->from_func->text().toDouble());
    (ui->to_func->text() == "")?(func_max = 100):(func_max = ui->to_func->text().toDouble());

    set_data(x_mas, y_mas, func_min, func_max);
    plot1();

    show_integral();
    }
}

void Widget::set_data(QVector<double> &x_mas, QVector<double> &y_mas, double x_min, double x_max){
    double section = (x_max-x_min);
    for (int i=0; i<section * 20 + 1; ++i)
    {
        x_mas << i/20.0 + x_min;
        y_mas << ResultExpr(tok, x_mas.back());
    }
}

void Widget::plot1(){
    ui->canva->graph(0)->setPen(QPen(Qt::red));
    ui->canva->graph(0)->setData(x_mas, y_mas);
    ui->canva->replot();
    ui->canva->update();
}

void Widget::plot_int(){
    ui->canva->graph(1)->setData(x_int, y_int);
    ui->canva->graph(1)->setPen(QPen(Qt::blue));
    ui->canva->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->canva->replot();
    ui->canva->update();
}

void Widget::plot_roots(){
    ui->canva->graph(2)->setPen(QPen(Qt::green));
    ui->canva->graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->canva->graph(2)->setLineStyle(QCPGraph::lsNone);

    ui->canva->graph(2)->setData(x_root, y_root);
    ui->canva->replot();
    ui->canva->update();
}

void Widget::clear_data(){
    x_mas.clear();
    y_mas.clear();
}

void Widget::clear_int(){
    x_int.clear();
    y_int.clear();
}

void Widget::clear_roots(){
    x_root.clear();
    y_root.clear();
}

void Widget::show_integral(){
    ui->findIntLabel->show();
    ui->fromLabel->show();
    ui->toLabel->show();
    ui->integral_a->show();
    ui->integral_b->show();
    ui->integralBut->show();
    ui->integralLabel->show();
    ui->root_but->show();
    ui->scrollArea->show();
}

void Widget::hide_integral(){
    ui->findIntLabel->hide();
    ui->fromLabel->hide();
    ui->toLabel->hide();
    ui->integral_a->hide();
    ui->integral_b->hide();
    ui->integralBut->hide();
    ui->integralLabel->hide();
    ui->root_but->hide();
    ui->scrollArea->hide();
}

void Widget::clear_canva(){
    clear_data();
    clear_int();
    clear_roots();
    plot1();
    plot_int();
    plot_roots();
    ui->root_list->clear();
}

void Widget::on_deleteBut_clicked()
{
    clear_canva();
    hide_integral();
    ui->lineEdit->clear();
    ui->root_list->clear();
}

void Widget::paint_integral(double a, double b){
    clear_int();

    set_data(x_int, y_int, a, b);

    plot_int();
}

void Widget::on_integralBut_clicked()
{
    double a,b;
    double res;
    a = ui->integral_a->text().toDouble();
    b = ui->integral_b->text().toDouble();

    res = integral(tok, a, b);
    if (res < 0.0001) res = 0;

    if (ui->integral_a->text() == "" || ui->integral_b->text() == "") {
        errorMessage.showMessage("Введите промежутки интегрирования!");
        errorMessage.exec();
    }
    else if (a > b){
        errorMessage.showMessage("a должно быть меньше b!");
        errorMessage.exec();
    }
    else {
        paint_integral(a,b);
        ui->integralLabel->setText("Интеграл равен: " + QString::number(res));
    }
}

void Widget::on_root_but_clicked()
{
    QString str = "";
    find_roots(tok, func_min, func_max, x_root, y_root);


    for (int i = 0; i < x_root.size(); i++) str += "( " + QString::number(x_root[i]) + " ; 0 ) \n";

    ui->root_list->setText(str);

    plot_roots();
}

void Widget::init_help(){
    help_str = "Введите функцию, зависящую от x.\nУмножение указывается явно: a*b\nДеление: a/b\nВозведение в степень: a^b\nКорень квадратный: sqrt(x)\nУгол указывается в радианах!\nСинус: sin(x)\nКосинус: cos(x)\nТангенс: tan(x)\nАрксинус: asin(x)\nАрккосинус: acos(x)\nАрктангенс: atan(x)\nМодуль: abs(x)\nЭкспонента (e^x): exp(x)\nНатуральный логарифм: log(x)\nЛогарифм по основанию 10: log10(x)\nЛогарифм по основанию 2: log2(x)\nЕсли нужно взять логарифм по другому основанию, можете воспользоваться формулой:\nlogb(a) = logy(a)/logy(b)";
}

void Widget::on_help_but_clicked()
{
    scroll_help->setWidget(help_window);
    scroll_help->verticalScrollBar()->setEnabled(false);
    scroll_help->horizontalScrollBar()->setEnabled(false);
    scroll_help->setWindowTitle("Справка");
    scroll_help->setFixedSize(700,450);
    help_window->setReadOnly(true);
    help_window->resize(700, 450);
    help_window->setFontPointSize(12);
    help_window->setText(help_str);
    scroll_help->show();
}

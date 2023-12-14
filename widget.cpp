#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->canva->setInteraction(QCP::iRangeDrag, true);
    ui->canva->setInteraction(QCP::iRangeZoom, true);

    ui->canva->xAxis->setRange(-10, 10);
    ui->canva->yAxis->setRange(-10, 10);

    ui->funcList->move(0, 0);
    ui->funcList->resize(this->width()/4, this->height());
    ui->canva->move(ui->funcList->width(), 0);
    ui->canva->resize(this->width()/8 * 7, this->height());
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    tokens tok;
    std::string function = ui->lineEdit->text().toStdString();

    ConvertToPostfix(function, tok);

    QVector<double> x, y; // initialize with entries 0..100
    for (int i=0; i<1000001; ++i)
    {
        x << i/10.0 - 50000;
        y << ResultExpr(tok, x.back());
    }
    // create graph and assign data to it:
    ui->canva->addGraph();
    ui->canva->graph(0)->setData(x, y);

    // give the axes some labels:
    ui->canva->xAxis->setLabel("x");
    ui->canva->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->canva->xAxis->setRange(-10, 10);
    ui->canva->yAxis->setRange(-10, 10);

    ui->canva->replot();
//----------------------------------------------------------------Connect slots and signals
//    QHBoxLayout *lay = new QHBoxLayout();
//    QVBoxLayout *left_lay = new QVBoxLayout(), *right_lay = new QVBoxLayout();
//    left_b.push_back(*left_lay);
//    right_b.push_back(*right_lay);
//    ui->verticalList_4->addLayout(lay);
//    setLayout(lay);


//    QPushButton *button_l1 = new QPushButton, *button_l2 = new QPushButton, *button_r1 = new QPushButton, *button_r2 = new QPushButton;
//    left_lay->addWidget(button_l1);
//    left_lay->addWidget(button_l2);
//    right_lay->addWidget(button_r1);
//    right_lay->addWidget(button_r2);

//    QLineEdit *edit = new QLineEdit;
//    ui->verticalList_4->addWidget(edit);

//    ui->verticalList_4->addLayout(right_lay);
}


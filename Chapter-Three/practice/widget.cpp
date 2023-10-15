#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_beg_clicked()
{
    ui->glWidget->timer->setInterval(1);
    ui->glWidget->timer->start();
}


void Widget::on_stop_clicked()
{
    ui->glWidget->timer->stop();
}

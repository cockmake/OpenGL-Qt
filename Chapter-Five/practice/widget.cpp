#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_setBtn_clicked()
{
    ui->openGLWidget->timer->setInterval(5);
    ui->openGLWidget->timer->start();
}

void Widget::on_stopBtn_clicked()
{
    ui->openGLWidget->timer->stop();
}

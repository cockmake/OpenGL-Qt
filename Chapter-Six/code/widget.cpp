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
    ui->openGLWidget->timer->setInterval(10);
    ui->openGLWidget->timer->start();
    auto p = ui->openGLWidget->mapToGlobal(ui->openGLWidget->rect().center());
    QCursor::setPos(p);
    ui->openGLWidget->setFocus();
}

void Widget::on_stopBtn_clicked()
{
    ui->openGLWidget->timer->stop();
}

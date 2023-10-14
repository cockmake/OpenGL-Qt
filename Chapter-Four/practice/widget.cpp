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
void Widget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_Up:
            ui->glWidget->changeR(0.1f);
            break;
        case Qt::Key_Down:
            ui->glWidget->changeR(-0.1f);
            break;
        default:
            break;
    }
}

void Widget::on_stop_clicked()
{
    ui->glWidget->timer->stop();
}

void Widget::on_start_clicked()
{
    ui->glWidget->timer->setInterval(1);
    ui->glWidget->timer->start();
}

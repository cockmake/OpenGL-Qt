#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :QWidget(parent) ,ui(new Ui::Widget){
    ui->setupUi(this);
//    ui->openGLWidget->setGeometry(this->geometry());
}
Widget::~Widget(){
    delete ui;
}

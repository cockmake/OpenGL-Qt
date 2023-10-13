#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <glm.hpp>
#include <QtOpenGL>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
using namespace std;
using namespace glm;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int c;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

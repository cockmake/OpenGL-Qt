#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QtOpenGL>
#include <chrono>
#include <iostream>
#include <thread>
#include <QThread>
#include <QRandomGenerator>
using namespace std;
using namespace chrono;

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
    void keyPressEvent(QKeyEvent *e) override;

private slots:
    void on_start_clicked();

    void on_stop_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

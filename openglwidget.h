#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <iostream>
using namespace std;
class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:

};

#endif // OPENGLWIDGET_H

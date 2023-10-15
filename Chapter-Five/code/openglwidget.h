#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <iostream>

using namespace std;
class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:

};

#endif // OPENGLWIDGET_H

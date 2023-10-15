#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}
void OpenGLWidget::paintGL()
{

}

void OpenGLWidget::initializeGL()
{

}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout << w << '\t' << h << endl;
}



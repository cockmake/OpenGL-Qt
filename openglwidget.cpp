#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent): QOpenGLWidget(parent)
{
    cout<<"运行开始"<<endl;
}

void OpenGLWidget::initializeGL()
{

    initializeOpenGLFunctions();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout<<w<<' '<<h<<endl;
}

void OpenGLWidget::paintGL()
{
    // 窗口大小发生变化时会触发一次绘制
    // 函数使用之前必须要进行初始化，即指向显卡中的函数，否则函数为空指针
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    cout<<"运行结束"<<endl;
}

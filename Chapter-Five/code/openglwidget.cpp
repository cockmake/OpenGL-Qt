#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    tex(QOpenGLTexture::Target2D)
{

}

OpenGLWidget::~OpenGLWidget()
{


}
void OpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderP.bind();
    shaderP.setUniformValue("model", model);
    shaderP.setUniformValue("view", view);
    shaderP.setUniformValue("projection", projection);



}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    bool success = shaderP.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/shader.vert");
    if(success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }
    success = shaderP.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shader.frag");
    if(success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout << w << '\t' << h << endl;
}



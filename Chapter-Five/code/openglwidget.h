#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <iostream>
#include <QImage>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
using namespace std;
class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    QMatrix4x4 model, view, projection;
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    GLuint VAO, VBO, EBO;
    QOpenGLTexture tex;
    QOpenGLShaderProgram shaderP;
signals:

};

#endif // OPENGLWIDGET_H

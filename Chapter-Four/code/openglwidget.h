#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <iostream>
#include <glm.hpp>
#include <stb_image.h>
#include <QImage>
#include "shader.h"

using namespace std;
using namespace glm;

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    static float vertices[];
    static GLuint indices[];
protected:
    GLuint texture;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    uchar *data;
    int width, height, nc;
    GLuint VAO, VBO, EBO;
    Shader *shaderProgram;
signals:

};

#endif // OPENGLWIDGET_H

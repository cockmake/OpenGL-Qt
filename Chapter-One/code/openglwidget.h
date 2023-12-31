﻿#ifndef OPENGLWIDGET_H
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
    ~OpenGLWidget();
    static float vertices[], rectangle[];
    static GLuint indices[];
    GLuint VBO, VAO, EBO;
    const char *vertexShaderSource =  "#version 450 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "void main()\n"
                                      "{\n"
                                      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                      "}\0";
    // FragColor不是预定义的输出变量，因此需要使用out关键字，读者也可以自定义变量名。
    const char *fragmentShaderSource =  "#version 450 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                        "}\0";
    GLuint vertexShader, fragmentShader, shaderProgram;


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:

};

#endif // OPENGLWIDGET_H

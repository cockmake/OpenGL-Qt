#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <iostream>
#include <QtOpenGL>
#include <QOpenGLFunctions_4_5_Core>
#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QImage>
#include <QMatrix4x4>
#include <chrono>
#include <QVector>

using namespace std;
using namespace chrono;
class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    GLuint VAO, VBO;
    static float vertices[], verticesWithColors[];
    float greenColor = 1.0f, bias = 0.0f;
    int cur_v = 0;
    void setGreenColor();
    QTimer *timer;

    GLuint vertexShader, fragmentShader, shaderProgram;

    QOpenGLShaderProgram shaderP;
    QOpenGLTexture texture;
    QMatrix4x4 trans, trans2;
    ~OpenGLWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

signals:

};

#endif // OPENGLWIDGET_H

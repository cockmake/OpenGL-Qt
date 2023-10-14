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
#include <chrono>
#include <QOpenGLTexture>
#include <QImage>
#include <QKeyEvent>

using namespace std;
using namespace chrono;
class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    GLuint VAO, VBO;
    static float vertices[], verticesWithColors[], verticesPoly[];
    int cur_v = 0;
    void setGreenColor();
    QTimer *timer;
    QOpenGLShaderProgram shaderP;
    QOpenGLTexture texture0, texture1;
    ~OpenGLWidget();
    void changeR(float v);
protected:
    float greenColor = 1.0f, bias = 0.0f, r = 0.5f;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

signals:

};

#endif // OPENGLWIDGET_H

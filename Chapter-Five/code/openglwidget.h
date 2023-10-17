#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <iostream>
#include <QImage>
#include <QOpenGLTexture>
#include <QVector>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QDebug>
#include <QException>
#include <QTimer>
using namespace std;
class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    int cur_v = 0;
    QTimer *timer;
    QMatrix4x4 model, view, projection;
    static float vertices[], cubeVertices[];
    static GLuint indices[];

    void setTrans();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QVector <QVector3D> cubePositions;
    GLuint VAO, VBO, EBO;
    QOpenGLTexture tex;
    QOpenGLShaderProgram shaderP;
signals:
};

#endif // OPENGLWIDGET_H

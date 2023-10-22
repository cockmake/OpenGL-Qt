#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLWidget>
#include <iostream>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QOpenGLBuffer>
using namespace std;
class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    static float rectangleVertices[];
    static GLuint indices[];
    void initTransMatrix();

    ~OpenGLWidget();
protected:
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;

private:
    QVector <QVector3D> objectPositions;
    float fov = 45.0;
    QVector <QMatrix4x4> views;
    QMatrix4x4 projection, model;
    GLuint VAO, VBO, EBO;
    QOpenGLTexture tex;
    QOpenGLShaderProgram shaderP;
    QVector3D coral{ 1.0f, 0.5f, 0.3f };
signals:
};

#endif // OPENGLWIDGET_H

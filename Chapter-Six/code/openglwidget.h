#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QMouseEvent>
#include <iostream>
#include <QImage>
#include <QOpenGLTexture>
#include <QVector>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QDebug>
#include <QException>
#include <QTimer>
#include <QTime>
#include <QtMath>
#include <QCursor>
#include <QWheelEvent>
#include <cmath>
#include <unordered_set>
#include <QTimerEvent>

using namespace std;
class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    int cur_v = 0;
    QTimer *timer;
    QMatrix4x4 model, projection;
    static float vertices[], cubeVertices[];
    static GLuint indices[];
    void setTrans();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    float sensitivity, fov, speed;
    int lastX, lastY;
    float pitch, yaw;
    bool enableMouse = true;
    unordered_set<int> keys;
    QVector3D cameraPos, cameraTarget, cameraDirection, cameraRight, cameraUp;
    QVector<QMatrix4x4> views;
    QVector <QVector3D> cubePositions;
    GLuint VAO, VBO, EBO;
    QOpenGLTexture tex;
    QOpenGLShaderProgram shaderP;
    void mouseMoveEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void timerEvent(QTimerEvent *e) override;
    int timer_id;
signals:
};

#endif // OPENGLWIDGET_H

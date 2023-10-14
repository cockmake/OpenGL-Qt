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
    const char *vertexShaderSource = "#version 450 core\n"
                                     "layout(location = 0) in vec3 aPos;\n"
                                     "out vec4 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos, 1.0f);\n"
                                     "   vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
                                     "}\n";
    const char *vertexShaderSourceWithColor = "#version 450 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec4 outColor;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos, 1.0f);\n"
        " outColor = vec4(aColor, 1.0f);\n"
        "}\n";

    const char *fragmentShaderSource = "#version 450 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec4 vertexColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vertexColor;\n"
                                       "}\n";

    const char *fragmentShaderSourceFromUniform = "#version 450 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = ourColor;\n"
        "}\n";

    const char *fragmentShaderSourceWithColor = "#version 450 core\n"
        "in vec4 outColor;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "   fragColor = outColor;\n"
        "}\n";

    GLuint vertexShader, fragmentShader, shaderProgram;

    QOpenGLShaderProgram shaderP;

    ~OpenGLWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

signals:

};

#endif // OPENGLWIDGET_H

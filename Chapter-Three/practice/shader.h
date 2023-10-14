#ifndef SHADER_H
#define SHADER_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Shader: public QOpenGLFunctions_4_5_Core{
public:
    GLuint shaderProgram;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    // 激活程序
    void use();
    // uniform工具函数
    void setBool(const string& name, GLboolean v);
    void setInt(const string& name, GLint v);
    void setFloat(const string& name, GLfloat v);
};

#endif // SHADER_H

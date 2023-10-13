#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 位移（1， 1， 0）
    vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    mat4 tt = translate(mat4(1.0f), vec3(1.0f, 1.0f, 0.0f));
    vec = tt * vec;
    cout << vec.x << vec.y << vec.z << endl;
    // 旋转90度，然后放缩0.5倍
    tt = rotate(mat4(1.0f), radians(90.0f), vec3(0.0f, 0.0f, 1.0f));
    tt = scale(tt, vec3(0.5f, 0.5f, 0.5f));

    /*
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;
    out vec2 TexCoord;

    uniform mat4 transform;

    void main()
    {
        gl_Position = transform * vec4(aPos, 1.0f);
        TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    }
    GLuint transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(t));
    */
}

Widget::~Widget()
{
    delete ui;
}


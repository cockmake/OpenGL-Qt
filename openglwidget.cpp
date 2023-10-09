#include "openglwidget.h"

float OpenGLWidget::vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};
OpenGLWidget::OpenGLWidget(QWidget *parent): QOpenGLWidget(parent)
{
    cout<<"运行开始"<<endl;
}

void OpenGLWidget::initializeGL()
{
    // 绑定本地函数指针
    initializeOpenGLFunctions();

    //创建VBO，VAO，并赋予ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定到VBO，VAO对象上
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    //如果data不是nullptr，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //告知显卡如何解析缓冲区里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          static_cast<void*>(0));

    //开启VAO管理第一个属性值
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout<<w<<' '<<h<<endl;
}

void OpenGLWidget::paintGL()
{
    // 任何绘制之前都要有6大部分
    /*
     * 定点着色器（必须）
     * 形状装配器
     * 几何着色器
     * 光栅化
     * 片段着色器（必须）
     * 测试与混合
    */
    // 窗口大小发生变化时会触发一次绘制
    // 函数使用之前必须要进行初始化，即指向显卡中的函数，否则函数为空指针
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    cout<<"运行结束"<<endl;
}

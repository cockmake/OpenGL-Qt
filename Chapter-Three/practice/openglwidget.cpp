#include "openglwidget.h"

float OpenGLWidget::vertices[] =
{
    -0.5f, 0.5f, 0.0f, // 左上
    0.0f, -0.5f, 0.0f, // 正下
    0.5f, 0.5f, 0.0f // 右上
};
float OpenGLWidget::verticesWithColors[] =
{
    // 位置              // 颜色
    -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f
};
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&]()
    {
        setGreenColor();
    });
}

void OpenGLWidget::setGreenColor()
{
    cur_v = (cur_v + 1) % 314;
    // time_point current_time = system_clock::now();
    // long long time_value = current_time.time_since_epoch().count();
    float target_value = sin(static_cast<float>(cur_v) / 100.0f);
    greenColor = target_value;
    bias = target_value;
    update();
}

OpenGLWidget::~OpenGLWidget()
{
    // 回收对应的资源
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    cout << "program over" << endl;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;

    // 创建VAO，VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 启动VAO，给VBO绑定数据，并且告知如何解析该部分数据
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesWithColors), verticesWithColors, GL_STATIC_DRAW);

//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//                          static_cast<void *>(0));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          static_cast<void *>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // 构建顶点着色器和片段着色器
    bool success = shaderP.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/shader.vert");
    if(!success)
    {
        cout << shaderP.log().toStdString() << endl;
    }
    success = shaderP.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shader.frag");
    if(!success)
    {
        cout << shaderP.log().toStdString() << endl;
    }
    success = shaderP.link();
    if(!success)
    {
        cout << shaderP.log().toStdString() << endl;
    }

    glBindVertexArray(0);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    shaderP.bind();
    shaderP.setUniformValue("bias", bias);


    glBindVertexArray(VAO); // 绑定所要使用的VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0); // 使用完以后进行解绑
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout << "w: " << w << " h: " << h << endl;
}

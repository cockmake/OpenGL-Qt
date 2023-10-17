#include "openglwidget.h"
float  OpenGLWidget::vertices[] = {
    //局部坐标    //纹理坐标
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f,   0.5f, 0.0f, 1.0f, 1.0f
};
float  OpenGLWidget::cubeVertices[] = {
    //局部坐标    //纹理坐标
    // 前面四个点
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
    0.5f,  -0.5f,  0.5f, 1.0f, 0.0f,
    0.5f,   0.5f,  0.5f, 1.0f, 1.0f,
    // 后面四个点
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,   0.5f, -0.5f, 1.0f, 1.0f,
    // 下边四个点
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    0.5f,  -0.5f,  0.5f, 1.0f, 1.0f,
    // 上边四个点
    0.5f,   0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    0.5f,   0.5f,  0.5f, 1.0f, 1.0f,
    // 右边四个点
    0.5f,   0.5f,  0.5f, 0.0f, 1.0f,
    0.5f,   0.5f, -0.5f, 0.0f, 0.0f,
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  -0.5f,  0.5f, 1.0f, 1.0f,
    // 左边四个点
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
};
GLuint OpenGLWidget::indices[] = {
    0,   1,  2,  3,
    4,   5,  6,  7,
    8,   9, 10, 11,
    12, 13, 14, 15,
    16, 17, 18, 19,
    20, 21, 22, 23,
    24, 25, 26, 27
};
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    tex(QOpenGLTexture::Target2D)
{
    cout << 111 << endl;
    cubePositions = QVector <QVector3D> {
        { 0.0f, 0.0f, -3.0f },
        { 2.0f, 5.0f, -18.0f },
        { -1.5f, -2.2f, -5.5f },
        { -3.8f, -2.0f, -15.3f },
        { 2.4f, -0.4f, -6.5f },
        { -1.7f, 3.0f, -10.5f },
        { 1.3f, -2.0f, -5.5f },
        { 1.5f, 2.0f, -5.5f },
        { 1.5f, 0.2f, -4.5f },
        { -1.3f, 1.0f, -4.5f }
    };
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&](){
        setTrans();
    });
    cout << this->width() << '\t' << this->height() << endl;
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shaderP.destroyed();
}

void OpenGLWidget::setTrans()
{
    cur_v = (cur_v + 1) % 618;

    model.setToIdentity();
//    view.setToIdentity();
    projection.setToIdentity();

    float v = sin(static_cast <float>(cur_v) / 50.0f);
    model.translate(QVector3D(v, -v, 0.0f));
    model.rotate(static_cast <float>(cur_v) * 18 / 3.14, QVector3D(1.0f, 0.5f, 0.3f));

//    view.translate(0.0f, 0.0f, -3.0f);
    projection.perspective(45.0f, static_cast <float>(this->width()) / static_cast <float>(this->height()),
                           0.1f, 100.0f);
    update();
}

void OpenGLWidget::paintGL()
{
//    cout << 333 << endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderP.bind();
    tex.bind(1);

    glBindVertexArray(VAO);
    shaderP.setUniformValue("model", model);
    shaderP.setUniformValue("projection", projection);
    for (int i = 0; i < cubePositions.size(); i++)
    {
        view.setToIdentity();
        view.translate(cubePositions[i]);
        shaderP.setUniformValue("view", view);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, nullptr);
    }
    glBindVertexArray(0);
//    cout << 444 << endl;
}

void OpenGLWidget::initializeGL()
{
    cout << 222 << endl;
    // 数据的初始化 写在这里
    // 注意initializeGL的时候widget的大小会发生变化所以要重新设置一下projection矩阵
    cout << this->width() << '\t' << this->height() << endl;
    setTrans();

    initializeOpenGLFunctions();

    bool success = shaderP.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/shader.vert");
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }
    success = shaderP.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shader.frag");
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }
    // 绑定好顶点着色器和片段着色器以后一定不要忘记进行链接
    success = shaderP.link();
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // VAO干的事情

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast <void *>(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast <void *>(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    tex.create();
    tex.setData(QImage(":/images/face.png").mirrored());
    tex.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    tex.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    tex.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Nearest);

    // 开启深度测试
    // 运行过程中不变化的数据在这里初始化就可以了
    glEnable(GL_DEPTH_TEST);

    shaderP.bind();
    shaderP.setUniformValue("tex", 1);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glBindVertexArray(0);
}

void OpenGLWidget::resizeGL(int w, int h)
{
//    cout << w << '\t' << h << endl;
}

#include "openglwidget.h"

float OpenGLWidget::vertices[] =
{
    // 位置   //纹理采样点
    -0.5f,  0.5f,              0.0f, /*左上*/ 0.0f, 1.0f,
    -0.5f, -0.5f,              0.0f, /*左下*/ 0.0f, 0.0f,
    0.5f,  -0.5f,              0.0f, /*右下*/ 1.0f, 0.0f,
    0.5f,   0.5f,              0.0f, /*右上*/ 1.0f, 1.0f
};
float OpenGLWidget::verticesWithColors[] =
{
    // 位置              // 颜色
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.0f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f,   0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    texture(QOpenGLTexture::Target2D)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&]()
    {
        setGreenColor();
    });
}

void OpenGLWidget::setGreenColor()
{
    // 该函数只用该修改变量，修改的变量的使用在paintGL里面
//    time_point current_time = system_clock::now();
//    long long time_value = current_time.time_since_epoch().count();

    cur_v = (cur_v + 1) % 314;

    float target_value = sin(static_cast <float>(cur_v) / 100.0f);
//    greenColor = target_value;
    bias = target_value;
    float r = static_cast <float>(cur_v) * 1.8f / 3.1415;
    trans.setToIdentity();   // 顺序和读的顺序相反
    trans.translate(0.5, -0.5f, 0.0f);
    trans.rotate(r, QVector3D(1.0f, 0.0f, 0.0f));

    trans2.setToIdentity();
    trans2.translate(-0.5, 0.5f, 0.0f);
    trans2.scale(QVector3D(bias, bias, 1.0f));
    trans2.rotate(r, QVector3D(1.0f, 0.0f, 0.0f));
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          reinterpret_cast <void *>(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          reinterpret_cast <void *>(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    // 构建顶点着色器和片段着色器
    bool success = shaderP.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/shader.vert");
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
    }
    success = shaderP.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shader.frag");
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
    }
    success = shaderP.link();
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
    }

    // 构建纹理
    texture.create();
    texture.setData(QImage(":/images/face.png").mirrored());
    texture.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    texture.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Nearest);


    shaderP.bind();
    // 非变化的初始化的时候绑定
    shaderP.setUniformValue("tex", 1); // 绑定前要使用
    texture.bind(1);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    shaderP.bind();
    texture.bind(1);
    // 变化的在绘制中进行绘制
    shaderP.setUniformValue("bias", bias);
    shaderP.setUniformValue("trans", trans);
    glBindVertexArray(VAO); // 绑定所要使用的VAO
    glDrawArrays(GL_POLYGON, 0, 4);

    // 绘制第二个
    shaderP.setUniformValue("trans", trans2);
    glDrawArrays(GL_POLYGON, 0, 4);
    glBindVertexArray(0); // 使用完以后进行解绑
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout << "w: " << w << " h: " << h << endl;
}

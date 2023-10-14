#include "openglwidget.h"

float OpenGLWidget::vertices[] =
{
    -0.5f, 0.5f, 0.0f, // 左上
    0.0f, -0.5f, 0.0f, // 正下
    0.5f, 0.5f, 0.0f // 右上
};

float OpenGLWidget::verticesPoly[] =
{
    // 想要取单个像素所有纹理位置相同即可

    // 位置               // 颜色                   // 纹理位置
    -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   /*左上*/0.25f, 0.75f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   /*左下*/0.25f, 0.25f,
    0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   /*右下*/0.75f, 0.25f,
    0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   /*右上*/0.75f, 0.75f
};

float OpenGLWidget::verticesWithColors[] =
{
    // 位置              // 颜色
    -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    texture0(QOpenGLTexture::Target2D),
    texture1(QOpenGLTexture::Target2D)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&]()
    {
        setGreenColor();
    });
}

void OpenGLWidget::setGreenColor()
{
    cur_v = (cur_v + 1) % 618;
    // time_point current_time = system_clock::now();
    // long long time_value = current_time.time_since_epoch().count();
    float target_value = sin(static_cast<float>(cur_v) / 100.0f);
    greenColor = target_value;
    bias = target_value;
    update();
}

OpenGLWidget::~OpenGLWidget()
{
    cout << "have closed" << endl;
    // 回收对应的资源
    makeCurrent();
    shaderP.destroyed();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void OpenGLWidget::changeR(float v)
{
    r += v;
    if(r >= 1.0f)
    {
        r = 1.0f;
    }
    else if(r <= 0.0f)
    {
        r = 0.0f;
    }
    update();
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPoly),
                 verticesPoly, GL_STATIC_DRAW);

//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//                          static_cast<void *>(0));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(0));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // 用完后记得取消绑定

    // 构建顶点着色器和片段着色器
//    bool success = shaderP.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceWithColor);
    bool success = shaderP.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/shader.vert");
    if(!success)
    {
        cout << shaderP.log().toStdString() << endl;
    }
//    success = shaderP.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceWithColor);
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

    // 构建纹理
    texture1.create();
    texture1.setData(QImage(":/images/container.jpg").mirrored());
    texture1.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture1.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
    texture1.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Nearest);

    texture0.create();
    texture0.setData(QImage(":/images/face.png").mirrored());
    texture0.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    texture0.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    texture0.setBorderColor(QColor(1.0f, 1.0f, 1.0f, 1.0f));

    texture0.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Nearest);




}

void OpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用链接后的程序，原生OpenGL版本
//    glUseProgram(shaderProgram);
//    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//    glUniform4f(vertexColorLocation, 0.0f, greenColor, 0.0f, 1.0f);  // 配合uniform关键词使用

    // QT版本的OpenGL
//    shaderP.bind();
//    int vertexColorLocation = shaderP.uniformLocation("ourColor");
//    shaderP.setUniformValue(vertexColorLocation, 0.0f, greenColor, 0.0f, 1.0f);


    shaderP.bind();
    texture0.bind(0);
    texture1.bind(1);
    // 与fragmentShader之间的交互
    shaderP.setUniformValue("bias", bias);
    shaderP.setUniformValue("r", r);
    shaderP.setUniformValue("texture0", 0);
    shaderP.setUniformValue("texture1", 1);
    glBindVertexArray(VAO); // 绑定所要使用的VAO
    glDrawArrays(GL_POLYGON, 0, 4);

    glBindVertexArray(0); // 使用完以后进行解绑
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout << "w: " << w << " h: " << h << endl;
}

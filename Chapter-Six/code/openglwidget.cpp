#include "openglwidget.h"
float OpenGLWidget::vertices[] =
{
    //局部坐标    //纹理坐标
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f,   0.5f, 0.0f, 1.0f, 1.0f
};
float OpenGLWidget::cubeVertices[] =
{
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
GLuint OpenGLWidget::indices[] =
{
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
    cubePositions = QVector <QVector3D>
    {
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
    sensitivity = 0.002;
    fov         = 45.0f;
    speed       = 0.05; // 移动速度问题一般需要根据不同设备进行动态计算
    timer_id    = 0;

    time_point now = system_clock::now();
    cout << now.time_since_epoch().count() << endl;


    views = QVector <QMatrix4x4>(10);
    // 摄像头相关的向量最好可以在GPU中计算
    cameraPos    = { 0.0f, 0.0f, 2.0f };
    cameraTarget = { 0.0f, 0.0f, 0.0f };

    // 叉乘快速得到右边的正交向量
    cameraDirection = cameraPos - cameraTarget;
    cameraRight     = QVector3D::crossProduct({ 0.0f, 1.0f, 0.0f }, cameraDirection);
    cameraUp        = QVector3D::crossProduct(cameraDirection, cameraRight);
    // 用这三个向量可以构建一个LookAt变化矩阵
    // 也可以使用QMatrix快速创建LookAt矩阵

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&]()
    {
        setTrans();
    });
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
    model.rotate(static_cast <float>(cur_v) * 18 / 3.14, QVector3D(1.0f, 0.5f, 0.3f));

    for (int i = 0; i < views.size(); i++)
    {
        views[i].setToIdentity();
        views[i].lookAt(cameraPos, cameraTarget, cameraUp);
        views[i].translate(cubePositions[i]);
    }

    projection.setToIdentity();
    projection.perspective(fov, static_cast <float>(this->width()) / static_cast <float>(this->height()),
                           0.1f, 100.0f);
    update();
}

void OpenGLWidget::paintGL()
{
    // 一帧的开始到下一帧的开始
    long long curTime = system_clock::now().time_since_epoch().count();

    deltaTime = curTime - lastTime;
    // 得出渲染一帧所需要的时间，默认时间单位为纳秒
    lastTime = curTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderP.bind();
    tex.bind(1);

    glBindVertexArray(VAO);
    shaderP.setUniformValue("model", model);
    shaderP.setUniformValue("projection", projection);
    for (int i = 0; i < cubePositions.size(); i++)
    {
        shaderP.setUniformValue("view", views[i]);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, nullptr);
    }
    glBindVertexArray(0);
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    float xoffset = sensitivity * (e->x() - lastX),
          yoffset = sensitivity * (lastY - e->y());

    lastX = e->x();
    lastY = e->y();

    pitch += yoffset;
    yaw   += xoffset;

    if (pitch > M_PI_2)
    {
        pitch = M_PI_2;
    }
    else if (pitch < -M_PI_2)
    {
        pitch = -M_PI_2;
    }

    cameraDirection.setX(cos(yaw) * cos(pitch));
    cameraDirection.setY(sin(pitch));
    cameraDirection.setZ(sin(yaw) * cos(pitch));

    cameraRight = QVector3D::crossProduct({ 0.0f, 1.0f, 0.0f }, cameraDirection);
    cameraUp    = QVector3D::crossProduct(cameraDirection, cameraRight);

    cameraTarget = cameraPos + cameraDirection;
}

void OpenGLWidget::keyPressEvent(QKeyEvent *e)
{
    // isAutoRepeat用于判断此按键的来源是否是长按
    keys.insert(e->key());
    if (!e->isAutoRepeat() && timer_id == 0)
    {
        timer_id = startTimer(5);
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *e)
{
    keys.erase(e->key());
    if (!e->isAutoRepeat() && timer_id != 0 && keys.empty()) //当没有按键按下且定时器正在运行，才关闭定时器
    {
        killTimer(timer_id);
        timer_id = 0;                                        //重置定时器id
    }
}

void OpenGLWidget::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0)
    {
        // 放大操作
        fov -= 5.0f;
    }
    else
    {
        // 缩小操作
        fov += 5.0f;
    }

    if (fov > 60.0f)
    {
        fov = 60.0f;
    }
    else if (fov < 30.0f)
    {
        fov = 30.0f;
    }
}

void OpenGLWidget::timerEvent(QTimerEvent *e)
{
    // 需要动态计算移动速度

    speed = SPEED_BASE * deltaTime;

    if (keys.count(Qt::Key_W))
    {
        cameraPos += speed * cameraDirection;
    }
    if (keys.count(Qt::Key_S))
    {
        cameraPos -= speed * cameraDirection;
    }
    if (keys.count(Qt::Key_A))                           //左
    {
        cameraPos += QVector3D::crossProduct(cameraDirection, cameraUp) * speed;
    }
    if (keys.count(Qt::Key_D))                           //右
    {
        cameraPos -= QVector3D::crossProduct(cameraDirection, cameraUp) * speed;
    }
    // 注意，我们对右向量进行了标准化。如果我们没对这个向量进行标准化，
    // 最后的叉乘结果会根据cameraFront变量返回大小不同的向量。如果我们不对向量进行标准化，
    // 我们就得根据摄像机的朝向不同加速或减速移动了，但如果进行了标准化移动就是匀速的。
}

void OpenGLWidget::initializeGL()
{
    // 数据的初始化 写在这里
    // 注意initializeGL的时候widget的大小会发生变化所以要重新设置一下projection矩阵
    lastX = this->rect().center().x(), lastY = this->rect().center().y();

    yaw = -M_PI_2, pitch = 0.0f;
    // yaw is initialized to -M_PI_2 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    // 想一想这里 yaw为什么设置成 -M_PI_2

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
    // 在这里初始化一些操作
    this->setMouseTracking(enableMouse);
    setTrans();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout << w << '\t' << h << endl;
}

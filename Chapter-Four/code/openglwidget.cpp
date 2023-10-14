#include "openglwidget.h"

float OpenGLWidget::vertices[] =
{
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
GLuint OpenGLWidget::indices[] =
{
    0, 1, 3,
    1, 2, 3
};
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    tex0(QOpenGLTexture::Target2D),
    tex1(QOpenGLTexture::Target2D)
{
    // stbi_set_flip_vertically_on_load(true);
    // data = stbi_load("D:\\QtProject\\OpenGL-Qt\\Chapter-Four\\code\\container.jpg", &width, &height, &nc, 0);
    // cout << width << '\t' << height << '\t' << nc << endl;
    // data1 = stbi_load("D:\\QtProject\\OpenGL-Qt\\Chapter-Four\\code\\face.png", &width1, &height1, &nc1, 0);
    // cout << width1 << '\t' << height1 << '\t' << nc1 << endl;

}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    glDeleteTextures(1, &texture);
    glDeleteTextures(1, &texture1);
    tex0.destroy();
    tex1.destroy();
    delete shaderProgram;
    doneCurrent();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // 构建着色程序
    shaderProgram = new Shader("D:\\QtProject\\OpenGL-Qt\\Chapter-Four\\code\\vertex_shader_source.vert",
                               "D:\\QtProject\\OpenGL-Qt\\Chapter-Four\\code\\fragment_shader_source.frag");


    // 初始化VAO，VBO对象
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(0));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    tex0.create();
    tex0.setData(QImage(":/images/face.png").mirrored());
    tex0.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
    tex0.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    tex0.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

    tex1.create();
    tex1.setData(QImage(":/images/container.jpg").mirrored());
    tex1.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
    tex1.setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    tex1.setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

//    激活对应纹理单元，获取ID，并绑定纹理
//    glActiveTexture(GL_TEXTURE0);
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    // 为当前绑定的纹理对象设置环绕、过滤方式
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//    if(data)
//    {
//        // 绑定对应数据
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
//                     0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        // 生成纹理，并释放原有内存
//        glGenerateMipmap(texture);
//        stbi_image_free(data);
//        cout << "texture load success!" << endl;
//    }

//    激活纹理以后进行绑定
//    glActiveTexture(GL_TEXTURE1);
//    glGenTextures(1, &texture1);
//    glBindTexture(GL_TEXTURE_2D, texture1);


//    // 为当前绑定的纹理对象设置环绕、过滤方式
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    if(data1)
//    {
//        // 绑定对应数据
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1,
//                     0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
//        // 生成纹理，并释放原有内存
//        glGenerateMipmap(texture1);
//        stbi_image_free(data1);
//        cout << "texture load success!" << endl;
//    }



    glBindVertexArray(0); // 配置完成以后解除绑定，需要时再次绑定
}

void OpenGLWidget::resizeGL(int w, int h)
{
    cout << w << '\t' << h << endl;
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->use();
    // 绑定到对应着色器中的texture单元
    tex0.bind(0);
    shaderProgram->setInt("ourTexture", 0);
    tex1.bind(1);
    shaderProgram->setInt("ourTexture1", 1);

    glBindVertexArray(VAO);
    glDrawArrays(GL_POLYGON, 0, 4);  // 可以直接使用 这个绘制多边形
    // glDrawElements 一般用于循环绘制
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

}


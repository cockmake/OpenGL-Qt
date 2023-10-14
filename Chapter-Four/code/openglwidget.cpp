#include "openglwidget.h"

float OpenGLWidget::vertices[] =
{
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
float OpenGLWidget::indices[] =
{
    0, 1, 3,
    1, 2, 3
};
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    data = stbi_load("D:\\QtProject\\OpenGL-Qt\\Chapter-Four\\code\\container.jpg", &width, &height, &nc, 0);
    cout << width << '\t' << height << '\t' << nc << endl;

}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    glDeleteTextures(1, &texture);
    delete shaderProgram;
    doneCurrent();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // 初始化VAO，VBO对象
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          static_cast<void *>(0));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // 激活对应纹理单元，获取ID，并绑定纹理
    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(data)
    {
        // 绑定对应数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                     0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // 生成纹理，并释放原有内存
        glGenerateMipmap(texture);
        stbi_image_free(data);
        cout << "texture load success!" << endl;
    }

    shaderProgram = new Shader("D:\\QtProject\\OpenGL-Qt\\Chapter-Four\\code\\vertex_shader_source.vert",
                               "D:\\QtProject\\OpenGL-Qt\\Chapter-Four\\code\\fragment_shader_source.frag");

    // 绑定到对应着色器中的texture单元

    shaderProgram->setInt("ourTexture", GL_TEXTURE0);

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
//    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

}


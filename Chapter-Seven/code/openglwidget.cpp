#include "openglwidget.h"
float  OpenGLWidget::rectangleVertices[] = {
    -0.5,  0.5,  0.5, 0.0, 1.0,
    -0.5, -0.5,  0.5, 0.0, 0.0,
    0.5,  -0.5,  0.5, 1.0, 0.0,
    0.5,   0.5,  0.5, 1.0, 1.0,

    -0.5,  0.5, -0.5, 0.0, 0.0,
    -0.5, -0.5, -0.5, 0.0, 1.0,
    0.5,  -0.5, -0.5, 1.0, 1.0,
    0.5,   0.5, -0.5, 1.0, 0.0
};
GLuint OpenGLWidget::indices[] = {
    0, 1, 2, 3,
    0, 4, 7, 3,
    7, 1, 2, 5,
    0, 1, 5, 4,
    7, 6, 2, 3,
    5, 4, 7, 6
};

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    tex(QOpenGLTexture::Target2D)
{
    objectPositions = {
        { 0.0, 0.0, -3.0 }
    };
    views = QVector <QMatrix4x4>(objectPositions.size());
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    shaderP.destroyed();
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VAO);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO);
    shaderP.bind();
    shaderP.setUniformValue("model", model);
    shaderP.setUniformValue("projection", projection);
    for (int i = 0; i < objectPositions.size(); i++)
    {
        shaderP.setUniformValue("view", views[i]);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    bool success = shaderP.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }
    success = shaderP.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }
    success = shaderP.link();
    if (!success)
    {
        cout << shaderP.log().toStdString() << endl;
        return;
    }
    else
    {
        cout << "the ShaderProgram have built" << endl;
    }
    glGenBuffers(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast <void *>(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast <void *>(3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    initTransMatrix();
}

void OpenGLWidget::resizeGL(int w, int h)
{
}

void OpenGLWidget::initTransMatrix()
{
    model.setToIdentity();
    model.rotate(45.0, QVector3D(1.0, 0.0, 0.0));

    projection.setToIdentity();
    for (int i = 0; i < objectPositions.size(); i++)
    {
        views[i].setToIdentity();
        views[i].translate(objectPositions[i]);
    }

    projection.perspective(fov, static_cast <float>(this->width()) / static_cast <float>(this->height()),
                           0.1f, 100.0f);
}

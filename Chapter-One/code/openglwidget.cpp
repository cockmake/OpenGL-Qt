#include "openglwidget.h"

float OpenGLWidget::vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

float OpenGLWidget::rectangle[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左G下角
    -0.5f, 0.5f, 0.0f   // 左上角
};
GLuint OpenGLWidget::indices[] = {
    0, 1, 3,
    1, 2, 3
};
OpenGLWidget::OpenGLWidget(QWidget *parent): QOpenGLWidget(parent)
{
    cout<<"运行开始"<<endl;
}

OpenGLWidget::~OpenGLWidget()
{
   glDeleteShader(shaderProgram);
   glDeleteBuffers(1, &VBO);
   glDeleteVertexArrays(1, &VAO);
}

void OpenGLWidget::initializeGL()
{
    // 绑定本地函数指针
    initializeOpenGLFunctions();

    // 创建一个着色器对象，注意还是用ID来引用的
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 绑定顶点着色器源码附加到着色器对象上，然后编译它：
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    GLint vertexSuccess;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
    char log[512];
    if(vertexSuccess){
        cout<<"构建着色器成功！"<<endl;
    }else{
        cout<<"构建着色器失败！"<<endl;
        glGetShaderInfoLog(vertexShader, 512, nullptr, log);
        cout<<log<<endl;
    }
    // 定义片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 绑定片段着色器源码并附加到着色器对象上，然后对他进行编译
    GLint fragmentSuccess;
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
    glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
    if(fragmentSuccess){
        cout<<"构建着色器成功！"<<endl;
    }else{
        cout<<"构建着色器失败！"<<endl;
        glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
        cout<<log<<endl;
    }

    // 构建渲染程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // 链接渲染程序
    glLinkProgram(shaderProgram);

    // 判断是否链接成功
    GLint programSuccess;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);

    if(!programSuccess){
        cout<<"渲染程序构建失败！"<<endl;
        glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
        cout<<log<<endl;
    }else{
        cout<<"渲染程序构建成功！"<<endl;
	// 在把着色器对象链接到程序对象以后，记得删除着色器对象，不再需要它们了：
    	glDeleteShader(vertexShader);
    	glDeleteShader(fragmentShader);

    }


    // VAO的作用
    // 创建VAO对象，并赋予ID
    glGenVertexArrays(1, &VAO);
    // 使用VAO对象上
    glBindVertexArray(VAO);
    // VBO， EBO主要是用来绑定数据的

    // 创建VBO，并赋予ID
    glGenBuffers(1, &VBO); // 申请ID
    // 绑定到VBO对象上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 为当前绑定到target的缓冲区对象创建一个新的数据存储
    // 如果data不是nullptr，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW); // 初始化缓存区对应的数据

    // 创建EBO，并赋予ID，注意EBO的状态要被VAO记录，VAO的绑定要在EBO的绑定之前
    glGenBuffers(1, &EBO);
    // 绑定到EBO对象上
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 为对顶缓存区绑定数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // 告知显卡如何解析缓冲区里的属性值，该配置信息会记录在VAO中
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          static_cast<GLvoid*>(0));
    // 开启VAO管理第一个属性值
    glEnableVertexAttribArray(0);

    // 当目标是GL_ELEMENT_ARRAY_BUFFER的时候，VAO会储存glBindBuffe的函数调用。
    // 这也意味着它也会储存解绑调用，所以确保你没有在解绑VAO之前解绑索引数组缓冲，
    // 否则它就没有这个EBO配置了。



    // 更换绘制模式为线条
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


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
     * 几何着色器（选择）
     * 光栅化
     * 片段着色器（必须）
     * 测试与混合
    */
    // 窗口大小发生变化时会触发一次绘制
    // 函数使用之前必须要进行初始化，即指向显卡中的函数，否则函数为空指针
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用链接后的程序
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // 绑定所要使用的VAO
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0); // 使用完以后进行解绑
    cout<<"运行结束"<<endl;
}

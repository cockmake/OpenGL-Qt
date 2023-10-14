#include "shader.h"
void Shader::setBool(const string &name, GLboolean value)
{
    GLint uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1i(uniformLocation, static_cast<GLint>(value));
}
void Shader::setInt(const string &name, GLint value)
{
    GLint uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1i(uniformLocation, value);
}
void Shader::setFloat(const string &name, GLfloat value)
{
    GLint uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1f(uniformLocation, value);
}
void Shader::setUint(const string &name, GLuint value)
{

    GLint uniformLocation = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1ui(uniformLocation, value);

}
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // 1. 从文件路径中获取顶点/片段着色器
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();


    // 2. 编译着色器
    initializeOpenGLFunctions();
    GLuint vertexShader, fragmentShader;
    GLint success;
    char infoLog[512];
    // 构建顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    // 打印编译错误（如果有的话）
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        cout << infoLog << endl;
    };

    // 构建片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        cout << infoLog << endl;
    };

    // 链接着色程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        cout << infoLog << endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    cout << "着色程序构建完成！" << endl;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}



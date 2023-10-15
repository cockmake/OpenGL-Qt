#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform float bias;
uniform mat4x4 trans;

out vec2 texCoord;
void main(void)
{
    gl_Position = trans * vec4(aPos, 1.0f);
    texCoord = aTexCoord;
}

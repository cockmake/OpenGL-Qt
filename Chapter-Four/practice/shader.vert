#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec4 outColor;
uniform float bias;

void main(void)
{
    gl_Position = vec4(aPos.x - bias, aPos.y, aPos.z, 0.8f);

    texCoord = aTexCoord;
    outColor = vec4(aColor, 1.0f);
}

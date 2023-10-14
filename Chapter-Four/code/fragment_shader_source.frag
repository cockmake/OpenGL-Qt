#version 450 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    fragColor = texture2D(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
    // 向量相乘只保留我们想要的颜色
}

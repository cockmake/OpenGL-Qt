#version 450 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;

void main()
{

    fragColor = mix(texture2D(ourTexture, TexCoord),
                    texture2D(ourTexture1, TexCoord), 0.8f);

//     fragColor = texture2D(ourTexture1, TexCoord) * vec4(ourColor, 1.0f);
//     向量相乘只保留我们想要的颜色

//    fragColor = vec4(ourColor, 1.0f);

}

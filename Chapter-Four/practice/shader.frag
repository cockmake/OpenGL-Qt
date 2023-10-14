#version 450 core
in vec4 outColor;
in vec2 texCoord;

out vec4 fragColor;
uniform sampler2D texture0, texture1;
uniform float r;
void main(void)
{
    // question1
//    fragColor = mix(texture2D(texture0, vec2(1.0f - texCoord.x, texCoord.y)),
//                    texture2D(texture1, texCoord), 0.5f);
    // question2
    fragColor = mix(texture2D(texture1, texCoord),
                    texture2D(texture0, texCoord), r);

//    fragColor = outColor;
}

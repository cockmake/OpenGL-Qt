#version 450 core
in vec4 outColor;

in vec3 bPos;
out vec4 fragColor;


void main(void)
{
    // question3
    fragColor = vec4(bPos, 1.0f);

//    fragColor = outColor;

}

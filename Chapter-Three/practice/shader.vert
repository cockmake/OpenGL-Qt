#version 450 core
in vec3 aPos;
in vec3 aColor;

out vec3 bPos;
out vec4 outColor;
uniform float bias;

void main(void)
{
    // question1
//    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0f);
    // question2
//    gl_Position = vec4(aPos.x - bias, aPos.y - bias, aPos.z, 1.0f);
    // question3
    gl_Position = vec4(aPos, 1.0f);

    bPos = aPos;
    outColor = vec4(aColor, 1.0f);
}

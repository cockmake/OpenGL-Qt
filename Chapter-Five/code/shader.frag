#version 450 core
in vec3 outColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D tex;
void main(){
    fragColor = texture2D(tex, texCoord);

}

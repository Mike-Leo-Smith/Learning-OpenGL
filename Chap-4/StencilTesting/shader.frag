#version 410 core

in vec2 texCoord;
in vec4 vertPos;

out vec4 fragColor;

uniform sampler2D sampler;

void main() {
    fragColor = texture(sampler, texCoord);
}
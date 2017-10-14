#version 410 core

in vec2 texCoord;
in vec4 vertPos;

out vec4 fragColor;

uniform sampler2D boxSampler;
uniform sampler2D faceSampler;

void main() {
    fragColor = mix(texture(boxSampler, texCoord), texture(faceSampler, texCoord), 0.5f);
}

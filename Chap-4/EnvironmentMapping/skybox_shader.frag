#version 410 core

in vec3 texDirection;
out vec4 fragColor;

uniform samplerCube sampler;

void main() {
    fragColor = texture(sampler, texDirection);
}

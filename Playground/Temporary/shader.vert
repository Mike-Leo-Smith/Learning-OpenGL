#version 410 core

layout (location = 0) in vec2 aVertPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

void main() {
    gl_Position = vec4(aVertPos, 0.0f, 1.0f);
    texCoord = aTexCoord;
}

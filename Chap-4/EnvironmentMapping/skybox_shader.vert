#version 410 core

layout (location = 0) in vec3 aPosition;

out vec3 texDirection;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    texDirection = aPosition;
    gl_Position = (projection * view * vec4(aPosition, 1.0f)).xyww;
}

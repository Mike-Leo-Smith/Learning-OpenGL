#version 410 core

layout (location = 0) in vec3 vertPos;
out vec4 vertColor;
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(vertPos, 1.0f);
    vertColor = vec4(vertPos * 0.5f + 0.5f, 1.0f);

    if (vertPos.x == 0 && vertPos.y == 0 && vertPos.z == 0) {
        gl_Position = mvp * vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
}

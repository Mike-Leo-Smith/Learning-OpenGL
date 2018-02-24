#version 410 core

layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 vert_tex_pos;

uniform mat4 mvp;

out vec2 frag_tex_pos;

void main() {
    gl_Position = mvp * vec4(vert_pos, 1.0f);
    frag_tex_pos = vert_tex_pos;
}

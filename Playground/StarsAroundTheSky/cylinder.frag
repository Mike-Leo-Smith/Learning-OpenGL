#version 410 core

in vec2 frag_tex_pos;
out vec4 frag_color;

uniform sampler2D sampler;
uniform vec4 color;

void main() {
    frag_color = texture(sampler, frag_tex_pos);
    if (frag_color.r > 0.5f) {
        discard;
    }
    frag_color = color;
}

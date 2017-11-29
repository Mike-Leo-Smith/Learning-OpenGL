#version 410 core

in vec2 texCoord;
out vec4 color;

uniform sampler2D sampler;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(sampler, texCoord).r);
    color = vec4(textColor, 1.0) * sampled;
}

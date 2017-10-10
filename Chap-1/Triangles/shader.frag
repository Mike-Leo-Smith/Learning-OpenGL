#version 410 core

in vec3 vertColor;
out vec4 fragColor;

uniform float alpha;

void main()
{
    fragColor = vec4(vertColor, alpha);
}
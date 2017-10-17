#version 410 core

in vec3 fragNormal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 fragColor = vec4(1.0f);

uniform sampler2D diffuse[8];
uniform int diffuseCount;

void main() {
    for (int i = 0; i < diffuseCount; i++) {
        fragColor *= texture(diffuse[i], texCoord);
    }
}

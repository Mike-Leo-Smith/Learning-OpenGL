#version 410 core

in vec3 fragNormal;
in vec3 fragPosition;

out vec4 fragColor;

uniform vec3 cameraPosition;
uniform samplerCube sampler;

void main() {
    vec3 cameraDir = normalize(fragPosition - cameraPosition);
    vec3 reflectionDir = reflect(cameraDir, normalize(fragNormal));
    fragColor = texture(sampler, reflectionDir);
}

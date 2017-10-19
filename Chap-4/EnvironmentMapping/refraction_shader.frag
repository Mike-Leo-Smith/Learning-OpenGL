#version 410 core

in vec3 fragNormal;
in vec3 fragPosition;

out vec4 fragColor;

uniform vec3 cameraPosition;
uniform samplerCube sampler;

void main() {
    vec3 cameraDir = normalize(fragPosition - cameraPosition);
    vec3 refractionDir = refract(cameraDir, normalize(fragNormal), 0.66f);
    fragColor = vec4(texture(sampler, refractionDir).rgb, 1.0f);
}

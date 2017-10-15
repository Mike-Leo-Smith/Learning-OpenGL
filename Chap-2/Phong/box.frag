#version 410 core

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 cameraPos;

const vec3 lightColor = vec3(1.0f);
const vec3 objectColor = vec3(1.0f, 0.5f, 0.31f);
const vec3 ambientColor = vec3(1.0f);
const float ambientStrength = 0.1f;
const float specularStrength = 0.5f;

void main() {
    vec3 ambient = ambientColor * ambientStrength;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 cameraDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, cameraDir), 0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    fragColor = vec4(objectColor * (ambient + diffuse + specular), 1.0f);
}

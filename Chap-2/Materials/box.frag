#version 410 core

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 cameraPos;
uniform Material material;
uniform Light light;

void main() {
    // Ambient.
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse.
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * light.diffuse;

    // Specular.
    vec3 cameraDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, cameraDir), 0), material.shininess);
    vec3 specular = spec * material.specular * light.specular;

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}

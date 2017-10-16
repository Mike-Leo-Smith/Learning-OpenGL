#version 410 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 fragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float outerCutOff;
};

uniform vec3 cameraPos;
uniform Material material;
uniform SpotLight light;

void main() {
    vec3 diffuseColor = vec3(texture(material.diffuse, texCoord));
    vec3 specularColor = vec3(texture(material.specular, texCoord));

    // Ambient.
    vec3 ambient = light.ambient * diffuseColor;

    // Diffuse.
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * diffuseColor * light.diffuse;

    // Specular.
    vec3 cameraDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, cameraDir), 0.0f), material.shininess);
    vec3 specular = spec * specularColor * light.specular;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    fragColor = vec4((ambient + diffuse + specular) * intensity, 1.0f);
}

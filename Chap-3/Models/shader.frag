#version 410 core

in vec3 fragNormal;
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

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 pos, vec3 cameraDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 pos, vec3 cameraDir);

uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;

const int pointLightCount = 4;
uniform PointLight pointLights[pointLightCount];

uniform vec3 cameraPos;
uniform Material material;

void main() {
    vec3 cameraDir = normalize(cameraPos - fragPos);
    vec3 normal = normalize(fragNormal);

    vec3 result = calcDirectionalLight(directionalLight, normal, cameraDir);
    for(int i = 0; i < pointLightCount; i++) {
        result += calcPointLight(pointLights[i], normal, fragPos, cameraDir);
    }
    result += calcSpotLight(spotLight, normal, fragPos, cameraDir);

    fragColor = vec4(result, 1.0);
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDir) {
    vec3 diffuseColor = vec3(texture(material.diffuse, texCoord));
    vec3 specularColor = vec3(texture(material.specular, texCoord));

    // Ambient.
    vec3 ambient = light.ambient * diffuseColor;

    // Diffuse.
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = diff * diffuseColor * light.diffuse;

    // Specular.
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, cameraDir), 0.0f), material.shininess);
    vec3 specular = spec * specularColor * light.specular;

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 pos, vec3 cameraDir) {
    vec3 diffuseColor = vec3(texture(material.diffuse, texCoord));
    vec3 specularColor = vec3(texture(material.specular, texCoord));

    // Ambient.
    vec3 ambient = light.ambient * diffuseColor;

    // Diffuse.
    vec3 lightDir = normalize(light.position - pos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = diff * diffuseColor * light.diffuse;

    // Specular.
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, cameraDir), 0.0f), material.shininess);
    vec3 specular = spec * specularColor * light.specular;

    // Attenuation.
    float distance = length(light.position - pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                    light.quadratic * distance * distance);

    return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 pos, vec3 cameraDir) {
    vec3 diffuseColor = vec3(texture(material.diffuse, texCoord));
    vec3 specularColor = vec3(texture(material.specular, texCoord));

    // Ambient.
    vec3 ambient = light.ambient * diffuseColor;

    // Diffuse.
    vec3 lightDir = normalize(light.position - pos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = diff * diffuseColor * light.diffuse;

    // Specular.
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, cameraDir), 0.0f), material.shininess);
    vec3 specular = spec * specularColor * light.specular;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    return (ambient + diffuse + specular) * intensity;
}

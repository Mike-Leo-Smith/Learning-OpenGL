#version 410 core

in highp vec3 fragmentPosition;
in highp vec3 fragmentNormal;
in highp vec2 fragmentTextureCoord;
in highp vec4 lightSpacePosition;

out highp vec4 fragmentColor;

uniform highp sampler2D shadowSampler;
uniform highp sampler2D diffuseSampler;
uniform highp vec3 lightDirection;
uniform highp vec3 cameraPosition;

float calculateShadow(vec4 rawPosition) {
    vec3 position = (rawPosition.xyz / rawPosition.w) * 0.5f + 0.5f;
    float currentDepth = position.z;

    if (currentDepth > 1.0f) {
        return 0.0f;
    }

    float shadow = 0.0f;
    float bias = max(0.05 * (1.0 - dot(fragmentNormal, lightDirection)), 0.005);
    vec2 texelSize = 1.0 / textureSize(shadowSampler, 0);

    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            float pcfDepth = texture(shadowSampler, position.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    return shadow / 9.0;
}

void main() {
    vec3 textureColor = texture(diffuseSampler, fragmentTextureCoord).rgb;
    vec3 normal = normalize(fragmentNormal);

    // Ambient.
    float ambientStrength = 0.15;

    // Diffuse.
    vec3 lightPosition = normalize(lightDirection);
    float diffuseStrength = max(dot(lightPosition, fragmentNormal), 0.0f);

    // Specular.
    vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
    vec3 halfway = normalize(lightPosition + cameraDirection);
    float specularStrength = pow(max(dot(halfway, fragmentNormal), 0.0f), 16.0f);

    float shadowStrength = calculateShadow(lightSpacePosition);
    vec3 color = (ambientStrength + (1 - shadowStrength) * (specularStrength + diffuseStrength)) * textureColor;

    fragmentColor = vec4(color, 1.0f);
}

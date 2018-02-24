#version 410 core

layout (location = 0) in highp vec3 vertexPosition;
layout (location = 1) in highp vec3 vertexNormal;
layout (location = 2) in highp vec2 vertexTextureCoord;

out highp vec3 fragmentPosition;
out highp vec3 fragmentNormal;
out highp vec2 fragmentTextureCoord;
out highp vec4 lightSpacePosition;

uniform highp mat4 projectionMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 modelMatrix;
uniform highp mat4 lightSpaceTransformMatrix;

void main() {

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0f);

    fragmentPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0f));
    fragmentNormal = transpose(inverse(mat3(modelMatrix))) * vertexNormal;
    fragmentTextureCoord = vertexTextureCoord;
    lightSpacePosition = lightSpaceTransformMatrix * modelMatrix * vec4(vertexPosition, 1.0f);
}

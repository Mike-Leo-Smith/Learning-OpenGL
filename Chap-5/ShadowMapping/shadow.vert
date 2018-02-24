#version 410 core

in highp vec3 vertexPosistion;

uniform highp mat4 lightSpaceMatrix;
uniform highp mat4 modelMatrix;

void main() {
    gl_Position = lightSpaceMatrix * modelMatrix * vec4(vertexPosistion, 1.0f);
}

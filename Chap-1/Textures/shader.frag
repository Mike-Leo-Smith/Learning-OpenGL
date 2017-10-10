#version 410

in vec3 vertColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texSampler;
uniform sampler2D anotherTexSampler;

void main()
{
    vec4 bgColor = mix(texture(texSampler, texCoord), vec4(vertColor, 1.0f), 0.5);
    vec4 faceColor = texture(anotherTexSampler, texCoord);

    if (faceColor.a > 0.1) {
        fragColor = faceColor;
    } else {
        fragColor = bgColor;
    }
}

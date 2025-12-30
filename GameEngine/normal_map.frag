#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec2 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;

in vec2 texCoord;
out vec4 fragColor;

void main()
{
    vec4 base = texture(diffuseMap, texCoord);

    vec3 normal = texture(normalMap, texCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    vec2 size = vec2(textureSize(diffuseMap, 0));
    vec2 fragPos = texCoord * size;

    vec3 lightDir = normalize(vec3(lightPos - fragPos, 150.0));

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 color = base.rgb * diff * lightColor * lightIntensity;
    fragColor = vec4(color, base.a);
}






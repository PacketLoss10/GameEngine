#version 130

#define MAX_LIGHTS 16

uniform sampler2D u_texture;
uniform sampler2D u_normalMap;
uniform int u_lightCount;
uniform vec2 u_lightPosition[MAX_LIGHTS];
uniform float u_lightRadius[MAX_LIGHTS];
uniform vec3 u_lightColor[MAX_LIGHTS];
uniform float u_lightBrightness[MAX_LIGHTS];

void main()
{
    vec4 baseColor = texture2D(u_texture, gl_TexCoord[0].xy);

    vec3 normal;
    if (textureSize(u_normalMap, 0).x > 0) // check if normal map is valid
    {
        vec3 normalColor = texture2D(u_normalMap, gl_TexCoord[0].xy).rgb;
        normal = normalize(normalColor * 2.0 - 1.0);
    }
    else
    {
        normal = vec3(0.0, 0.0, 1.0);
    }

    vec3 result = baseColor.rgb * 0.2;

    for (int i = 0; i < u_lightCount; i++)
    {
        vec2 fragPos = gl_FragCoord.xy;
        vec2 lightPos = u_lightPosition[i];

        float dist = distance(fragPos, lightPos);

        vec3 lightDir = normalize(vec3(lightPos - fragPos, u_lightRadius[i]));

        float diffuse = max(dot(normal, lightDir), 0.0);

        float intensity = (u_lightRadius[i] * u_lightRadius[i]) / (dist * dist + 1.0);
        intensity = clamp(intensity, 0.0, 1.0);

        result += baseColor.rgb * diffuse * intensity * u_lightColor[i] * u_lightBrightness[i];
    }

    gl_FragColor = vec4(result, baseColor.a);
}
#version 120

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
	vec3 normalColor = texture2D(u_normalMap, gl_TexCoord[0].xy).rgb;

    vec3 result = baseColor.rgb * 0.2; // ambient

    for (int i = 0; i < u_lightCount; i++)
    {
        float dist = distance(gl_FragCoord.xy, u_lightPosition[i]);

        vec3 lightDir = normalize(vec3(u_lightPosition[i] - gl_FragCoord.xy, u_lightRadius[i]));

        vec3 normal = normalize(normalColor * 2.0 - 1.0);

        float diffuse = max(dot(normal, lightDir), 0.0);

        float intensity = (u_lightRadius[i] * u_lightRadius[i]) / (dist * dist + 1.0);

        intensity = clamp(intensity, 0.0, 1.0);

        result += baseColor.rgb * diffuse * intensity * u_lightColor[i] * u_lightBrightness[i];
    }

    gl_FragColor = vec4(result, baseColor.a);
}
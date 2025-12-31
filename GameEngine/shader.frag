#version 120

uniform sampler2D u_texture;
uniform sampler2D u_normalMap;
uniform vec2 u_lightPosition;
uniform float u_lightRadius;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;

void main()
{
	vec4 baseColor = texture2D(u_texture, gl_TexCoord[0].xy);
	vec3 normalColor = texture2D(u_normalMap, gl_TexCoord[0].xy).rgb;

	float dist = distance(gl_FragCoord.xy, u_lightPosition);
	vec3 lightDir = normalize(vec3(u_lightPosition - gl_FragCoord.xy, u_lightRadius));
	vec3 normal = normalize(normalColor * 2.0 - 1.0);

	float diffuse = max(dot(normal, lightDir), 0.0);

	float intensity = (u_lightRadius * u_lightRadius) / (dist * dist + 1.0);
	intensity = clamp(intensity, 0.0, 1.0);

	vec3 litColor = baseColor.rgb * (0.2 + diffuse * intensity * u_lightColor * u_lightBrightness);

	gl_FragColor = vec4(litColor, baseColor.a);
}
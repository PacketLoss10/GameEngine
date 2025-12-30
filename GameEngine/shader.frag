#version 120

uniform sampler2D u_texture;
uniform vec2 u_position;
uniform float u_radius;

void main()
{
	float dist = distance(gl_FragCoord.xy,u_position);

	vec4 color = texture2D(u_texture, gl_TexCoord[0].xy);
	vec4 mod = vec4(1.0, 0.0, 0.0, 1.0);

	if (dist <= u_radius)
	{
		gl_FragColor = color * mod;
	}
	else
	{
		gl_FragColor = color;
	}
}
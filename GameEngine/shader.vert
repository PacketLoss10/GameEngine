#version 450 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 fragTexCoord;
out vec2 fragWorldPos;

uniform vec2 u_objectPosition; // sprite position
uniform mat4 u_proj;           // orthographic projection

void main()
{
    fragTexCoord = inTexCoord;
    fragWorldPos = inPosition + u_objectPosition;
    gl_Position = u_proj * vec4(inPosition + u_objectPosition, 0.0, 1.0);
}

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in float a_TexIndex;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform vec3 u_CameraPos;

out vec3 v_Position;
out vec4 v_Color;
flat out vec3 v_Normal;
out vec3 v_FragPosition;
out vec2 v_TexCoord;
flat out float v_TexIndex;
out float v_Distance;


void main()
{
    gl_Position = u_Projection * u_View * a_Position;
    v_Position = a_Position.xyz;
    v_Color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    v_Normal = a_Normal;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;

    v_Distance = distance(a_Position.xyz, u_CameraPos);
}
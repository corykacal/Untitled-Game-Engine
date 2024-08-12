#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out float v_TexIndex;
flat out float v_Deleted;
out float v_Distance;

uniform mat4 u_MVP;
uniform vec3 u_CameraPos;

void main()
{
    gl_Position = u_MVP * a_Position;
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;

    v_Distance = distance(a_Position.xyz, u_CameraPos);
}
#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in float a_TexIndex;

uniform mat4 u_Projection;
uniform mat4 u_View;

out vec3 v_Position;

void main()
{
    v_Position = a_Position.xyz;
    vec4 pos = u_Projection * mat4(mat3(u_View)) * a_Position;
    gl_Position = pos.xyww;
}
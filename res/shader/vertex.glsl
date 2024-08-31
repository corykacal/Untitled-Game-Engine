#version 410 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in float a_TexIndex;

out vec3 v_Position;
flat out mat3 v_TBN;
out vec2 v_TexCoord;
flat out float v_TexIndex;
out float v_Distance;

uniform mat4 u_MVP;
uniform vec3 u_CameraPos;

//don't have "model" at the moment. model is transform, rotation, scale
//Add model uniform list that is updated for memory saving

void main()
{
    gl_Position = u_MVP * a_Position;
    v_Position = a_Position.xyz;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;

    vec3 Normal = normalize(a_Normal);
    vec3 Tangent = normalize(a_Tangent);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Normal, Tangent);
    v_TBN = mat3(Tangent, Bitangent, Normal);

    v_Distance = distance(a_Position.xyz, u_CameraPos);
}
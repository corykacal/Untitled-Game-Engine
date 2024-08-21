#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec2 a_TexCoord;
layout(location = 4) in float a_TexIndex;

out vec3 v_Position;
out vec4 v_Color;
flat out vec3 v_Normal;
out vec3 v_FragPosition;
out vec2 v_TexCoord;
flat out float v_TexIndex;
out float v_Distance;

uniform mat4 u_MVP;
uniform vec3 u_CameraPos;

void main()
{
    //don't have "model" at the moment. model is transform, rotation, scale
    //light is model * a_Position
    //refactor each shape class to have transofmr, rotation, scale, model will be sent into vertex shader.
    //use trs to move model instead of coordinate thing I am doing. pass in "model"/"TRS" in here.
    gl_Position = u_MVP * a_Position;
    v_Position = a_Position.xyz;
    v_Color = a_Color;
    v_Normal = a_Normal;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;

    v_Distance = distance(a_Position.xyz, u_CameraPos);
}
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
flat in float v_TexIndex;

in float v_Distance;

uniform sampler2D u_Textures[16];
uniform int u_FogDistance;

void main()
{
    int index = int(v_TexIndex);
    vec4 texColor = texture(u_Textures[index], v_TexCoord);

    // Use this line to blend between v_Color and texColor based on v_TexIndex
    color = mix(v_Color, texColor, step(0.5, v_TexIndex));


    // Calculate the fog factor based on distance
    float fogFactor = clamp((v_Distance - u_FogDistance) / 200, 0.0, 1.0);
    color = mix(color, vec4(.8,.9,1,1), fogFactor);
}
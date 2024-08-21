#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
flat in vec3 v_Normal;
in vec2 v_TexCoord;
flat in float v_TexIndex;

in float v_Distance;

uniform sampler2D u_Textures[16];
uniform int u_FogDistance;
uniform vec3 u_AmbientLightColor;
uniform float u_AmbientLightStrength;
//TODO get rid of this with better solution
uniform vec3 u_LightPosition;
uniform vec3 u_LightColor;

void main()
{
    //base color
    int index = int(v_TexIndex);
    vec4 texColor = texture(u_Textures[index], v_TexCoord);
    color = mix(v_Color, texColor, step(0.5, v_TexIndex));

    //ambient light
    vec4 ambient = vec4(u_AmbientLightStrength * u_AmbientLightColor, 1.0f);

    //diffuse lighting
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPosition - v_Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(diff * u_LightColor, 1.0f);

    //final light calculation
    color = (ambient + diffuse) * color;

    //fog affect
    float fogFactor = clamp((v_Distance - u_FogDistance) / 200, 0.0, 1.0);
    color = mix(color, vec4(.8,.9,1,1), fogFactor);
}
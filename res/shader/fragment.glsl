#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
flat in mat3 v_TBN;
in vec2 v_TexCoord;
flat in float v_TexIndex;
in float v_Distance;

uniform sampler2D u_Textures[16];
uniform int u_FogDistance;
uniform vec3 u_AmbientLightColor;
uniform float u_AmbientLightStrength;
uniform vec3 u_LightPosition;
uniform vec3 u_LightColor;
uniform vec3 u_CameraPos;

void main()
{
    int index = int(v_TexIndex);
    vec3 viewDir = normalize(u_CameraPos - v_Position);

    float heightScale = 0.09f;
    float minLayers = 24.0f;
    float maxLayers = 32.0f;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0f, 0.0f, 1.0f), viewDir)));
    float layerDepth = 1.0f/numLayers;
    float currentLayerDepth = 0.0f;

    vec2 S = viewDir.xy / viewDir.z * heightScale;
    vec2 deltaUVs = S / numLayers;

    vec2 UVs = v_TexCoord;
    float currentDepthMapValue = 1.0f - texture(u_Textures[index+4], UVs).r;

    // Loop till the point on the heightmap is "hit"
    while(currentLayerDepth < currentDepthMapValue)
    {
        UVs -= deltaUVs;
        currentDepthMapValue = 1.0f - texture(u_Textures[index+4], UVs).r;
        currentLayerDepth += layerDepth;
    }

    // Apply Occlusion (interpolation with prev value)
    vec2 prevTexCoords = UVs + deltaUVs;
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = 1.0f - texture(u_Textures[index+4], prevTexCoords).r - currentLayerDepth + layerDepth;
    float weight = afterDepth / (afterDepth - beforeDepth);
    UVs = prevTexCoords * weight + UVs * (1.0f - weight);

    // Get rid of anything outside the normal range
    if(UVs.x > 1.0 || UVs.y > 1.0 || UVs.x < 0.0 || UVs.y < 0.0)
    discard;




    // Base color
    vec4 texColor = texture(u_Textures[index], UVs);
    color = mix(vec4(1.0f, 1.0f, 0.0f, 1.0f), texColor, step(0.5, v_TexIndex));

    // Normal map
    vec3 normalMap = texture(u_Textures[index+2], UVs).rgb;
    vec3 normal = normalize(v_TBN * (normalMap * 2.0 - 1.0));

    // Ambient light
    vec4 ambient = vec4(u_AmbientLightStrength * u_AmbientLightColor, 1.0f);

    // Diffuse lighting
    vec3 lightDir = normalize(u_LightPosition - v_Position);
    float diff = max(dot(normal, lightDir), 0.0);
    vec4 diffuse = vec4(diff * u_LightColor, 1.0f);

    // Specular lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec4 specular = vec4(0.5 * spec * u_LightColor, 1.0f);

    // Final light calculation
    color = (ambient + diffuse + specular) * color;

    // Fog effect
    float fogFactor = clamp((v_Distance - u_FogDistance) / 200, 0.0, 1.0);
    color = mix(color, vec4(0.8, 0.9, 1, 1), fogFactor);
}
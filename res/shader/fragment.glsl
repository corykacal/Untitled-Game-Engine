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

const float g_ParallaxEndDistance = 15.0f;
const float g_HeightScale = 0.09f;
const float g_GridSize = 1.0f;
const int CelShadingLayersDiff = 6;

vec2 parallaxMapping(vec2 texCoords, vec3 viewDir, float distanceFactor)
{
    float heightScale = g_HeightScale * (1.0 - distanceFactor);
    float numLayers = mix(32.0, 16.0, distanceFactor);
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy / viewDir.z * heightScale;
    vec2 deltaTexCoords = P / numLayers;

    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = 1.0 - texture(u_Textures[int(v_TexIndex)+4], currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = 1.0f - texture(u_Textures[int(v_TexIndex)+4], currentTexCoords).r;
        currentLayerDepth += layerDepth;
    }

    return currentTexCoords;
}

float celShade(float intensity, int layers)
{
    float celIntensity = 0.0;
    for (int i = 0; i < layers; i++)
    {
        float threshold = float(i) / float(layers);
        if (intensity > threshold)
        {
            celIntensity = threshold + (1.0 / float(layers));
        }
    }
    return celIntensity;
}

void main()
{
    vec3 viewDir = normalize(u_CameraPos - v_Position);
    float distanceFactor = smoothstep(0.0, g_ParallaxEndDistance, v_Distance);

    vec2 texCoords = v_TexCoord;

    if (distanceFactor < 1.0) {
        vec3 viewDirTangent = normalize(transpose(v_TBN) * viewDir);
        texCoords = parallaxMapping(v_TexCoord, viewDirTangent, distanceFactor);
    }

    vec4 texColor = texture(u_Textures[int(v_TexIndex)], texCoords);
    color = mix(vec4(1.0f, 1.0f, 0.0f, 1.0f), texColor, step(0.5, v_TexIndex));

    // Normal mapping with distance-based interpolation
    vec3 normalMap = texture(u_Textures[int(v_TexIndex)+2], texCoords).rgb;
    vec3 normal = normalize(v_TBN * (normalMap * 2.0 - 1.0));

    // Lighting calculations
    vec3 lightDir = normalize(u_LightPosition - v_Position);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4.0);

    // Apply cel shading
    diff = celShade(diff, CelShadingLayersDiff);

    // Combined lighting
    vec3 lighting = u_AmbientLightColor * u_AmbientLightStrength + u_LightColor * (diff + 0.5 * spec);

    color.rgb *= lighting;

    // Fog effect
    float fogFactor = clamp((v_Distance - float(u_FogDistance)) / 200.0, 0.0, 1.0);
    color = mix(color, vec4(0.8, 0.9, 1.0, 1.0), fogFactor);
}
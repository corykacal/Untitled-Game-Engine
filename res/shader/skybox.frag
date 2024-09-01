#version 410 core

layout(location = 0) out vec4 color;

in vec3 v_Position;

const vec3 bottomColor = vec3(0.8, 0.85, 1.0); // Light blue
const vec3 topColor = vec3(0.32, 0.27, 0.9); // Dark blue

void main()
{
    vec3 pos = normalize(v_Position);
    float t = (pos.y + 1.0) * 0.5; // Map from [-1, 1] to [0, 1]
    vec3 skyColor = vec3(0.75, 0.7, 1.0);
    skyColor = mix(vec3(0.9, 0.92, 1.0), mix(bottomColor, topColor, t), t);
    color = vec4(skyColor, 1.0);
}
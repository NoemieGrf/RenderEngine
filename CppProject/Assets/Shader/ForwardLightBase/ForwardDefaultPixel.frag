#version 430 core

#include "../Library/Light.glsl"
#define NR_POINT_LIGHTS 4

layout (location = 0) out vec4 color;

layout(location = 0) in vec3 v_FragPos;
layout(location = 1) in vec2 v_TexCoord;
layout(location = 2) in vec3 v_Normal;

layout(location = 0) uniform vec3 u_ViewPosition;
layout(location = 1) uniform DirLight u_DirLight;
layout(location = 2) uniform SpotLight u_SpotLight;
layout(location = 3) uniform Material u_Material;
layout(location = 4) uniform PointLight u_PointsLights[NR_POINT_LIGHTS];

void main()
{
    // properties
    vec3 norm = normalize(v_Normal);
    vec3 viewDir = normalize(u_ViewPosition - v_FragPos);

    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = CalcDirLight(u_DirLight, norm, viewDir, u_Material, v_TexCoord);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    result += CalcPointLight(u_PointsLights[i], norm, v_FragPos, viewDir, u_Material, v_TexCoord);
    // phase 3: spot light
    result += CalcSpotLight(u_SpotLight, norm, v_FragPos, viewDir, u_Material, v_TexCoord);

    color = vec4(result, 1.0);
}
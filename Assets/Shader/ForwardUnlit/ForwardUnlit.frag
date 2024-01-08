#version 430 core

layout (location = 0) in vec2 v_TexCoord;
layout (location = 1) in vec3 v_Normal;
layout (location = 0) out vec4 color;

layout (std140, binding = 0) uniform Color
{
    vec3 u_Color;
};

layout (location = 1) uniform sampler2D u_Texture;

void main()
{
    color = vec4(u_Color, 1) * texture(u_Texture, v_TexCoord);
}
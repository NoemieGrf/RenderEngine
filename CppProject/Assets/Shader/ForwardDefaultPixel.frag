#version 430 core

layout (location = 0) out vec4 color;

layout(location = 0) in vec2 v_TexCoord;
layout(location = 1) in vec3 v_Normal;

void main()
{
    color = vec4(v_TexCoord, 0, 1);
}
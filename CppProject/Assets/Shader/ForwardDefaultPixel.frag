#version 420 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;

void main()
{
    color = vec4(v_TexCoord, 0, 1);
}
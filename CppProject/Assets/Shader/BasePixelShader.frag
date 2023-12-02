#version 420 core

layout (location = 0) out vec4 color;

uniform sampler2D u_tex;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;

void main()
{
    // color = v_Color;
    color = texture(u_tex, v_TexCoord);
}
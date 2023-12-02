#version 420 core

layout (location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Tex;

void main()
{
    // color = v_Color;
    color = texture(u_Tex, v_TexCoord);
    //color = vec4(v_TexCoord, 0, 1);
}
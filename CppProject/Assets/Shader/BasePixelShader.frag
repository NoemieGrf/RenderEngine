#version 420 core

layout (location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Tex;
uniform sampler2D u_Tex2;

void main()
{
    // color = v_Color;
    vec4 color1 = texture(u_Tex, v_TexCoord);
    vec4 color2 = texture(u_Tex2, v_TexCoord);
    color = color1 * color2;
    //color = vec4(v_TexCoord, 0, 1);
}
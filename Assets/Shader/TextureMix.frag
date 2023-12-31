#version 430 core

layout (location = 0) in vec2 v_TexCoord;

layout (location = 0) out vec4 color;

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
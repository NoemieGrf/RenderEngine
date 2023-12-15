#version 450

layout(location = 0) in vec2 in_var_TEXCOORD0;
layout(location = 0) out vec4 out_var_SV_TARGET;

void main()
{
    out_var_SV_TARGET = vec4(in_var_TEXCOORD0, 0.0, 1.0);
}


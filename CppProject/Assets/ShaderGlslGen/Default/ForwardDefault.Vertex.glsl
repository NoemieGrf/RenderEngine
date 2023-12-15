#version 450

layout(binding = 0, std140) uniform type_ModelBuffer
{
    layout(row_major) mat4 u_ModelMatrix;
} ModelBuffer;

layout(binding = 1, std140) uniform type_ViewBuffer
{
    layout(row_major) mat4 u_ViewMatrix;
} ViewBuffer;

layout(binding = 2, std140) uniform type_ProjectionBuffer
{
    layout(row_major) mat4 u_ProjectionMatrix;
} ProjectionBuffer;

layout(location = 0) in vec3 in_var_POSITION0;
layout(location = 1) in vec3 in_var_NORMAL0;
layout(location = 2) in vec2 in_var_TEXCOORD0;
layout(location = 0) out vec2 out_var_TEXCOORD0;
layout(location = 1) out vec3 out_var_NORMAL0;

mat4 spvWorkaroundRowMajor(mat4 wrap) { return wrap; }

void main()
{
    out_var_TEXCOORD0 = in_var_TEXCOORD0;
    out_var_NORMAL0 = in_var_NORMAL0;
    gl_Position = ((vec4(in_var_POSITION0, 1.0) * spvWorkaroundRowMajor(ModelBuffer.u_ModelMatrix)) * spvWorkaroundRowMajor(ViewBuffer.u_ViewMatrix)) * spvWorkaroundRowMajor(ProjectionBuffer.u_ProjectionMatrix);
}


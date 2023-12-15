cbuffer ModelBuffer : register(b0)
{
    float4x4 u_ModelMatrix;
}

cbuffer ViewBuffer : register(b1)
{
    float4x4 u_ViewMatrix;
}

cbuffer ProjectionBuffer : register(b2)
{
    float4x4 u_ProjectionMatrix;
}

struct VS_INPUT
{
    float3 a_Position : POSITION0;
    float3 a_Normal : NORMAL0;
    float2 a_TexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
    float2 v_TexCoord : TEXCOORD0;
    float3 v_Normal : NORMAL0;
    float4 gl_Position : SV_POSITION;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.v_TexCoord = input.a_TexCoord;
    output.v_Normal = input.a_Normal;
    output.gl_Position = mul(u_ProjectionMatrix, mul(u_ViewMatrix, mul(u_ModelMatrix, float4(input.a_Position, 1.0))));
    return output;
}
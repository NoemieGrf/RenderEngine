struct PS_INPUT
{
    float2 v_TexCoord : TEXCOORD0;
    float3 v_Normal : NORMAL0;
};

struct PS_OUTPUT
{
    float4 color : SV_TARGET;
};

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    output.color = float4(input.v_TexCoord, 0, 1);
    return output;
}
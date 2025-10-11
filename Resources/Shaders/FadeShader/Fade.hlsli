cbuffer ConstBuffer	: register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
    float  mode;
    float  time;
    float2 dammy;
};

struct VS_INPUT
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};


struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};
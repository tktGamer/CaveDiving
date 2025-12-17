cbuffer ConstBuffer	: register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color: COLOR;
	float2 tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};
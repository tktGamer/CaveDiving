cbuffer ConstBuffer	: register(b0)
{
	float2 windowSize;
	float alphaData;
	//アニメーションする時間
	float animationTime;
	//経過時間
	float currentTime;
	//総枚数
    int frameCount;
	//横の枚数
    int widthNum;
	//縦の枚数
    int heightNum;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color: COLOR;
	float2 tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 color: COLOR;
	float2 tex : TEXCOORD;
};
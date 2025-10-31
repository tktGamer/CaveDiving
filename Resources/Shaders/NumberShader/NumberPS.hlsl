#include "Number.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	‰æ‘œ•\Ž¦

    float2 uv = input.tex;
    float w = 10.0f;
    float h = 1.0f;
    uv.x /= w;
    uv.y /= h;
    uv.x += (1.0f / w) * (dammy % w);
    //uv.y += (1.0f / h) * (int) (floor(time.x) / w);
    
    float4 output = tex.Sample(samLinear, uv);
    output.r = lerp(0, 1, output.w);
    return output;
}
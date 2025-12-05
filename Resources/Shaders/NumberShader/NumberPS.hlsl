#include "Number.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	
    //•\¦‚·‚é”š‚ğ‹‚ß‚é
    float2 uv = input.tex;
    float w = 10.0f;
    float h = 1.0f;
    uv.x /= w;
    uv.y /= h;
    uv.x += (1.0f / w) * (number % w);
    uv.y += (1.0f / h) * (number / h);
    
    float4 output = tex.Sample(samLinear, uv);
    
    //‚ ‚éF‚Ì•”•ª‚ÌF‚ğ•Ï‚¦‚é
    float3 white = float3(1, 1, 1);
    output = lerp(output, numberColor, all(output.xyz == white));
    return output;
}
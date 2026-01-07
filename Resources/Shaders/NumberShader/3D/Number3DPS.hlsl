#include "Number3D.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{

	//	‰æ‘œ•\Ž¦
    float2 uv = input.Tex;
    float w = 10.0f;
    float h = 1.0f;
    uv.x /= w;
    uv.y /= h;
    uv.x += (1.0f / w) * (input.Color.w % w);
    uv.y += (1.0f / h) * (input.Color.w / h);
    
    float4 output = tex.Sample(samLinear, uv);
    output.xyz *= input.Color.xyz;
    output.xyz = lerp(output.xyz, output.xyz + 0.8f, input.Tex.y);
    //return lerp(output, output*2, input.Tex.y);
    return output;
}
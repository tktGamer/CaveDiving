#include "KeyUI.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	‰æ‘œ•\¦
	float4 output = tex.Sample(samLinear, input.tex);

	//­‚µˆÃ‚ß‚É‚·‚é	
    output.xyz *= lerp(1.0f, 0.5f, isPresesd);
	return output;
}
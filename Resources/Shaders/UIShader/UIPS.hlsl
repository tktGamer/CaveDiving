#include "UI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	‰æ‘œ•\Ž¦
	float4 output = tex.Sample(samLinear, input.tex);

	//	‰æ‘œ•\Ž¦‚»‚Ì2
    float4 output2 = tex2.Sample(samLinear, input.tex);
	

    float smoothValue = alphaData;
    output.a *= lerp(1.0f, 0.0f, smoothstep(smoothValue,smoothValue+0.5f, input.tex.x));
	return output;
}
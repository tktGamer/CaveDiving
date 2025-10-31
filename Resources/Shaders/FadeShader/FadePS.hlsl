#include "Fade.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
	
	//	黒ピクセル
    float4 outputb = float4(0, 0, 0, 1);
	
	//	if文で中央から丸く切り抜く
    float aspect = 1280.0f / 720.0f;
    float2 uv = input.Tex;
    uv.x *= aspect;

    float getDistance = distance(uv, float2(0.5f * aspect, 0.5f)) * 0.85f;
    float circleLength = abs(sin(time));

    // 2通りのalpha計算
    float alphaA = step(getDistance, circleLength); // モード0
    float alphaB = step(circleLength, getDistance); // モード1

    // modeが0.0ならalphaB、1.0ならalphaAになる
    float alpha = lerp(alphaB, alphaA, mode);

    outputb = lerp(outputb, float4(outputb.rgb, 0), alpha);

    return outputb;
}
#include "ModelShader.hlsli"


cbuffer CbLight : register(b1)
{
    float3 LightPosition ; // ライト位置
    float  LightInvSqrRadius; // ライトが届く距離（2乗の逆数)
    float3 LightColor; // ライトカラー
    float  LightIntensity ; // ライト強度
    float4 Attenuation;

}


//	C++側から設定されるデータ②
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float SmoothDistanceAttenuation
(
    float squareDistance, // ライトからの距離の2乗
    float invSqrAttRadius // ライトが届く距離の2乗の逆数
)
{
    
    float factor = squareDistance * invSqrAttRadius;
    float smoothFactor = saturate(1.0f - factor * factor);
    return (smoothFactor *smoothFactor);
}
#define MIN_DIST (0.01)

float GetDistanceAttenuation
(
    float3 unnormalizedLightVector, // ライト位置とピクセル位置の差分
    float invSqrAttRadius // ライトが届く距離の2乗の逆数
)
{
    float len = length(unnormalizedLightVector);
    len = Attenuation.x + Attenuation.y * len + Attenuation.z * len * len;
    float attenuation = 1.0f / (max(len, MIN_DIST * MIN_DIST));
    
    attenuation *= SmoothDistanceAttenuation(len, invSqrAttRadius);
    
    return attenuation;
}
float4 main(PS_IN input) : SV_TARGET
{
       
    float att = GetDistanceAttenuation(
        LightPosition - input.Posw.xyz,
        LightInvSqrRadius);
    
    float4 output = tex.Sample(samLinear, input.Tex);
    float3 tem = output.xyz * LightColor * LightIntensity * att;
    output.xyz = min(tem, output.xyz);
    output.w = 1.0f;
    
    return output;
}
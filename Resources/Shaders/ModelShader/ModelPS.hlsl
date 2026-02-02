#include "ModelShader.hlsli"

struct LightStruct
{
    float3 LightPosition; // ライト位置
    float  LightInvSqrRadius; // ライトが届く距離（2乗の逆数)
    float3 LightColor; // ライトカラー
    float  LightIntensity; // ライト強度
    float4 Attenuation; //減衰

};


//ライト情報
cbuffer CbLight : register(b1)
{
    LightStruct lights[8];
    int onLightCount;
    float3 dummy;
}

//	C++側から設定されるデータ②
Texture2D tex : register(t0);
Texture2D toonMap : register(t1);
SamplerState samLinear : register(s0);


float3 ToonStep(float intensity)
{    
    //トゥーンステップ
    float4 map = toonMap.Sample(samLinear, float2(intensity,0));
    return map.xyz;
}

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
    float4 Attenuation //距離減衰パラメータ
)
{
    //ライトからピクセルまでの距離
    float len = length(unnormalizedLightVector);
    //距離減衰計算
    len = Attenuation.x + Attenuation.y * len + Attenuation.z * len * len;
    
    //最小距離補正
    float attenuation = 1.0f / (max(len, MIN_DIST * MIN_DIST));
    
    
    return attenuation;
}
float4 main(PS_IN input) : SV_TARGET
{
    
    
    //元の画像の色
    float4 output = tex.Sample(samLinear, input.Tex);
    //return output;
    //すべてのライトからの距離を考慮した色
    float3 temTotal=0;
    for (int i = 0; i < onLightCount; i++)
    {
        //ライトからの距離減衰
        float intensity = GetDistanceAttenuation
        (
        lights[i].LightPosition - input.Posw.xyz,
        lights[i].Attenuation
        );
        

        //ライトからの距離を考慮した色
        float3 tem = output.xyz * lights[i].LightColor * lights[i].LightIntensity * ToonStep(intensity);
        temTotal += tem;
    }
    
    //元の色より明るくしないようにする
    output.xyz = min(temTotal, output.xyz);
    //透明度は固定
    output.w = 1.0f;
    
    return lerp( output,float4(1,1,1,1), color.x);
    
}
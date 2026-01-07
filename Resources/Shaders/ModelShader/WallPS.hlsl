#include "ModelShader.hlsli"

struct LightStruct
{
    float3 LightPosition; // ライト位置
    float  LightInvSqrRadius; // ライトが届く距離（2乗の逆数)
    float3 LightColor; // ライトカラー
    float  LightIntensity; // ライト強度
    float4 Attenuation; //減衰

};



cbuffer CbLight : register(b1)
{
    LightStruct lights[8];
    int onLightCount;
    float3 dummy;
}


cbuffer CameraPlayerCB : register(b2)
{
    float3 cameraPos;
    float fadeRadius;
    float3 playerPos;
    float fadestrength;//0.0f-1.0f
}

//	C++側から設定されるデータ②
Texture2D tex : register(t0);
Texture2D toonMap : register(t1);
SamplerState samLinear : register(s0);


float3 ToonStep(float intensity)
{
    //// トゥーンステップ（3段階）
    //if (intensity > 0.46f)
    //    return 0.9f;
    //else if (intensity > 0.33f)
    //    return 0.6f;
    //else if(intensity> 0.25f)
    //    return 0.1f;
    //else
    //    return 0.0f;
    
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
    float invSqrAttRadius, // ライトが届く距離の2乗の逆数
    float4 Attenuation
)
{
    float len = length(unnormalizedLightVector);
    len = Attenuation.x + Attenuation.y * len + Attenuation.z * len * len;
    float attenuation = 1.0f / (max(len, MIN_DIST * MIN_DIST));
    
   // attenuation *= SmoothDistanceAttenuation(len, invSqrAttRadius);
    
    return attenuation;
}
float4 main(PS_IN input) : SV_TARGET
{
    
    
    //元の画像の色
    float4 output = tex.Sample(samLinear, input.Tex);
    //return output;
    
    
    //すべてのライトからの距離を考慮した色
    float3 temTotal = 0;
    for (int i = 0; i < onLightCount; i++)
    {
        float intensity = GetDistanceAttenuation
        (
        lights[i].LightPosition - input.Posw.xyz,
        lights[i].LightInvSqrRadius,
        lights[i].Attenuation
        );
        

        //ライトからの距離を考慮した色
        float3 tem = output.xyz * lights[i].LightColor * lights[i].LightIntensity * ToonStep(intensity);
        //tem = diffuse;
        temTotal += tem;
    }
    
    //元の色より明るくしないようにする
    output.xyz = min(temTotal, output.xyz);
    
    //カメラとプレイヤーの間の線分を求める
    float3 camToPlayer = playerPos - cameraPos;
    //
    float camToPlayerLen = length(camToPlayer);
    float3 dir = camToPlayer / camToPlayerLen;
    
    //ピクセルが線分上のどこにあるか
    float t = dot(input.Posw.xyz - cameraPos, dir);
    
    //線分からの距離
    float tClamped = clamp(t, 0.0f, camToPlayerLen);
    float3 closet = cameraPos+dir * tClamped;
    float distToLine = length(input.Posw.xyz - closet);
    
    float alpha = 1.0f;
    
    //線分上の半径内を透過
    if (t > 0 && t < camToPlayerLen && distToLine < fadeRadius)
    {
        float fade = saturate(1.0 - distToLine / fadeRadius);
        alpha = lerp(1.0f, fadestrength, fade);
        
    }
    
    
    output.a *= alpha;
    return output;
}
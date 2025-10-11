#include "LumiRockShader.hlsli"

struct LightStruct
{
    float3 LightPosition; // ライト位置
    float LightInvSqrRadius; // ライトが届く距離（2乗の逆数)
    float3 LightColor; // ライトカラー
    float LightIntensity; // ライト強度
    float4 Attenuation; //減衰

};



cbuffer CbLight : register(b1)
{
    LightStruct lights[8];
    int onLightCount;
    float3 dummy;
}




//	C++側から設定されるデータ②
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float3 ToonStep(float intensity)
{
    // トゥーンステップ（3段階）
    if (intensity > 0.46f)
        return 0.9f;
    else if (intensity > 0.33f)
        return 0.6f;
    else if(intensity> 0.25f)
        return 0.1f;
    else
        return 0.0f;
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
    
    //attenuation *= SmoothDistanceAttenuation(len, invSqrAttRadius);
    
    return attenuation;
}
float4 main(PS_IN input) : SV_TARGET
{
    
    
    //元の画像の色
    float4 output = tex.Sample(samLinear, input.Tex);
    
    ////ライトからの距離を考慮した色
    //float3 tem = output.xyz * LightColor * LightIntensity * att;
    
    //すべてのライトからの距離を考慮した色
    float3 temTotal=0;
    for (int i = 0; i < onLightCount; i++)
    {
        float intensity = GetDistanceAttenuation
        (
        lights[i].LightPosition - input.Posw.xyz,
        lights[i].LightInvSqrRadius,
        lights[i].Attenuation
        );
        
        //法線を正規化する
        float3 worldNormal = normalize(input.Norw);
    
        float lightDirection = distance(lights[i].LightPosition, input.Posw.xyz);
        ////光の強さを内積で求める
        float3 dotL = dot(-lightDirection, worldNormal);
    
        //表面(+の範囲)の場合は１、裏面(-の範囲)の場合は０ 
        float3 zeroL = step( 0.0f, dotL);
        //裏面のときは黒になる
        float3 diffuse = zeroL * dotL;

        //ライトからの距離を考慮した色
        float3 tem = output.xyz * lights[i].LightColor * lights[i].LightIntensity * ToonStep(intensity);
        //tem = diffuse;
        temTotal += tem;
    }
    
    //元の色より明るくしないようにする
    output.xyz = min(temTotal, output.xyz);
   // output.rgb = saturate(temTotal);
    output.a = 1.0f;
    //透明度は固定
    //output.w = 1.0f;
    
    output = lerp(output, output + color, color.w);

    
    return output;
}
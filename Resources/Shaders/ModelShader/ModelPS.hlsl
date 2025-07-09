#include "ModelShader.hlsli"


cbuffer CbLight : register(b1)
{
    float3 LightPosition ; // ���C�g�ʒu
    float  LightInvSqrRadius; // ���C�g���͂������i2��̋t��)
    float3 LightColor; // ���C�g�J���[
    float  LightIntensity ; // ���C�g���x
    float4 Attenuation;

}


//	C++������ݒ肳���f�[�^�A
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float SmoothDistanceAttenuation
(
    float squareDistance, // ���C�g����̋�����2��
    float invSqrAttRadius // ���C�g���͂�������2��̋t��
)
{
    
    float factor = squareDistance * invSqrAttRadius;
    float smoothFactor = saturate(1.0f - factor * factor);
    return (smoothFactor *smoothFactor);
}
#define MIN_DIST (0.01)

float GetDistanceAttenuation
(
    float3 unnormalizedLightVector, // ���C�g�ʒu�ƃs�N�Z���ʒu�̍���
    float invSqrAttRadius // ���C�g���͂�������2��̋t��
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
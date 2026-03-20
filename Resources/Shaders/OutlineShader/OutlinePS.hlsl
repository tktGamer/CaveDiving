#include "OutLineShader.hlsli"

//	C++側から設定されるデータ②
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float4 main(PS_IN input) : SV_TARGET
{    
    //白色で出力
    return float4(1,1,1,1);
}
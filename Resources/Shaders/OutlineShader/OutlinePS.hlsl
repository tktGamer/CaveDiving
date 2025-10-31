#include "OutLineShader.hlsli"

//	C++‘¤‚©‚çİ’è‚³‚ê‚éƒf[ƒ^‡A
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float4 main(PS_IN input) : SV_TARGET
{    
    
    return float4(1,1,1,1);
}
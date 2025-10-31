#include "OutLineShader.hlsli"

VS_OUT main(VS_IN input)
{
 //   VS_OUT output = (VS_OUT)0;
    
 //   output.Pos = float4(input.Pos, 1);
 //   output.Nor = float4(input.Nor, 1);
	////	‘¼‚Í‚»‚Ì‚Ü‚Ü“n‚·
 //   output.Tex = input.Tex;
    
 //   return output;
    
    
    VS_OUT output = (VS_OUT) 0;
    
    output.Pos.xyz = input.Pos + input.Nor * OutlineThickness;
    output.Pos.w = 1.0f;
    
    return output;
}
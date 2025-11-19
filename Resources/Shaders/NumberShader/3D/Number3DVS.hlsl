#include "Number3D.hlsli"

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = float4(input.pos,1);
    
	output.Color = input.color;
	output.Tex = input.tex;
	return output;
}
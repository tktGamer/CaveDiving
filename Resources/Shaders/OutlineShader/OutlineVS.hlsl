#include "OutLineShader.hlsli"

VS_OUT main(VS_IN input)
{    
    VS_OUT output = (VS_OUT) 0;
    //“ü—Í‚³‚ê‚½ƒTƒCƒY‚ÉŠg‘å‚·‚é
    output.Pos.xyz = input.Pos + input.Nor * OutlineThickness;
    output.Pos.w = 1.0f;
    
    return output;
}
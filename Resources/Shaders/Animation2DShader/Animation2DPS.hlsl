#include "Animation2D.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	
    //uv座標
    float2 uv = input.tex;
    //テクスチャの横分割数
    float w = widthNum;
    //テクスチャの縦分割数
    float h = heightNum;
    //一コマ分のサイズにする
    uv /= float2(w, h);
    //進行率
    float rate = currentTime/ animationTime;
    rate = saturate(rate);
    //進行率からフレーム番号を算出
    int frame = (int) (frameCount * rate);
    //範囲外にならないよう制限
    frame = min(frame, frameCount - 1);

    //横方向フレーム位置
    int frameX = (frame % widthNum);
    uv.x += (1.0f /w) * frameX;
    //縦方向フレーム位置
    int frameY = (frame / widthNum);
    uv.y += (1.0f / h) * frameY;
    //計算したUVを使ってサンプリング
    float4 output = tex.Sample(samLinear, uv);
    //最終的な色を返す
    return output;
}
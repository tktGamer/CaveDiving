//	b0にはマトリックス3つとディフューズ情報を構造体として入れることにする
cbuffer ConstBuffer : register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
    // 押し出しの量
    float OutlineThickness; 
    float3 dummy;
};

struct VS_IN
{
    float3 Pos : POSITION; //頂点座標
    float3 Nor : NORMAL; //頂点法線
};

struct VS_OUT
{
    float4 Pos : SV_Position; //頂点座標
   
};

struct PS_IN
{
    float4 Pos : SV_POSITION;//計算済み座標
};
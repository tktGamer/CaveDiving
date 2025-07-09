//	b0にはマトリックス3つとディフューズ情報を構造体として入れることにする
cbuffer ConstBuffer : register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
    float4 light;
};

struct VS_IN
{
    float3 Pos : POSITION; //頂点座標
    float3 Nor : NORMAL; //頂点法線
    float2 Tex : TEXCOORD;
};

struct VS_OUT
{
    float4 Pos : SV_Position; //頂点座標
    float4 Nor : NORMAL0; //頂点法線
    float2 Tex : TEXCOORD;
   
};

struct PS_IN
{
    float4 Pos : SV_POSITION;//計算済み座標
    float4 Posw : POSITION0; //ワールド座標
    float4 Norw : NORMAL0; //ワールド座標の法線
    float2 Tex : TEXCOORD;
    
};
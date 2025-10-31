#include "Particle.hlsli"

//	4つの頂点を作成する
static const int vnum = 4;

//	各頂点のベースとする情報
static const float4 offset_array[vnum] =
{
	float4(-0.5f,  0.5f, 0.0f, 0.0f),	//	左上
	float4( 0.5f,  0.5f, 0.0f, 0.0f),	//	右上
	float4(-0.5f, -0.5f, 0.0f, 0.0f),	//	左下
	float4( 0.5f, -0.5f, 0.0f, 0.0f),	//	右下

};

//cbuffer CameraBuffer : register(b1)
//{
//    float3 cameraRight;
//    float dummy;
//    float3 cameraUp;
//    float dummy2;
    
//}



//[maxvertexcount(vnum)]
//void main(
//	point PS_INPUT input[1],
//	inout TriangleStream<PS_INPUT> output
//)
//{
//	//	4つの頂点を生成していく
//    for (int i = 0; i < vnum; i++)
//    {
//		//	新しい頂点情報用の変数
//        PS_INPUT element;

//		//	ベースの座標を取得
//        float4 res = offset_array[i];

//		//	Texに入っている情報で表示サイズを決定する。
//		//	その計算結果を、表示したい位置まで移動。
//        element.Pos = input[0].Pos + mul(offset_array[i] * input[0].Tex.x, matWorld);

		
//		//	viewとprojを計算して、スクリーン座標へ変換
//        element.Pos = mul(element.Pos, matView);
//        element.Pos = mul(element.Pos, matProj);

//		//	色情報はそのまま使う
//        element.Color = input[0].Color;
//		//	C++からもらっているTex情報はUV座標ではないため、
//		//	実際に使用可能な画像のUV情報をここで算出する
//        element.Tex.x = offset_array[i].x + 0.5f;
//        element.Tex.y = -offset_array[i].y + 0.5f;

//		//	次のシェーダへ情報を渡すため、頂点情報を追加する
//        output.Append(element);
//    }
	
//	//	生成した頂点データから、ポリゴン情報を適切に判断してもらう
//    output.RestartStrip();
//}

// カメラの定数バッファ
cbuffer CameraBuffer : register(b1)
{
    float3 cameraPos;
    float dummy1;
    float3 cameraUp;
    float dummy2;
}

[maxvertexcount(4)]
void main(
    point PS_INPUT input[1],
    inout TriangleStream<PS_INPUT> output
)
{
    float3 center = input[0].Pos.xyz;

    // カメラ方向（Z軸）
    float3 toCam = normalize(cameraPos - center);

    // ビルボードの軸を作る（右と上）
    float3 right = normalize(cross(cameraUp, toCam));
    float3 up = normalize(cross(toCam, right));

    float size = input[0].Tex.x; // スケールに使う

    for (int i = 0; i < 4; i++)
    {
        PS_INPUT element;

        // ローカルオフセット（[-0.5, 0.5]）
        float2 offset = offset_array[i].xy;

        // オフセットベクトルをビルボード軸に変換
        float3 offsetPos = (right * offset.x + up * offset.y) * size;

        // ワールド空間の頂点位置
        float3 worldPos = center + offsetPos;

        // ビュー・プロジェクション変換
        element.Pos = mul(float4(worldPos, 1.0f), matView);
        element.Pos = mul(element.Pos, matProj);

        // UV座標を算出（[-0.5, 0.5] → [0, 1]）
        element.Tex.xy = offset + 0.5f;

        // カラーなどはそのまま
        element.Color = input[0].Color;

        output.Append(element);
    }

    output.RestartStrip();
}
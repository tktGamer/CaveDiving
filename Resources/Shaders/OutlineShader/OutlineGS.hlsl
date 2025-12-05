#include "OutLineShader.hlsli"
//	頂点の数を定数として用意しておく
static const int vnum = 3;


[maxvertexcount(vnum)]
void main(
	triangle VS_OUT input[3],
	inout TriangleStream<PS_IN> output
)
{
	//	入力として渡された頂点1つに対して、4つに増やす作業を行う
    for (int i = 0; i < 3; i++)
    {
        PS_IN element;
		
		//	頂点シェーダが出力した座標に、増殖させるポリゴンのi番目の座標を計算する
        element.Pos = mul(input[i].Pos, matWorld);

		//	上記の結果に、ビュー行列を掛け算する
        element.Pos = mul(element.Pos, matView);
		//	上記の結果に、プロジェクション行列を掛け算する
        element.Pos = mul(element.Pos, matProj);

		
		//	ストリームへ頂点情報を追加する		
        output.Append(element);
    }
	
    output.RestartStrip();
}

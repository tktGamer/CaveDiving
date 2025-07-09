#include "ModelShader.hlsli"
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
        element.Posw = mul(input[i].Pos, matWorld);

		//	上記の結果に、ビュー行列を掛け算する
        element.Pos = mul(element.Posw, matView);
		//	上記の結果に、プロジェクション行列を掛け算する
        element.Pos = mul(element.Pos, matProj);
        // ワールド座標の法線を計算
        element.Norw = mul(input[i].Nor, matWorld);
		//	ポリゴンに表示するテクスチャのUV情報を算出する		
        element.Tex = input[i].Tex;

		
		//	ストリームへ頂点情報を追加する		
        output.Append(element);
    }
	
	//	追加した情報を適切に処理して、次のシェーダへ渡せるように再構成する。
	//	今回はTriangleStreamとなるため、三角形ポリゴン用の頂点データとして次のシェーダへデータが渡せるよう、
	//	良い感じに処理される
	//	※これ以降にAppendで追加しても、それまでの三角形ポリゴンとは別の「グループ」のポリゴンとなってしまう
    output.RestartStrip();
}

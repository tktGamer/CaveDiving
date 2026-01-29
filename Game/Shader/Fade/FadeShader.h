/**
 * @file   FadeShader.h
 *
 * @brief  フェード用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Shader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief フェード用シェーダー
  */
class FadeShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//フェードシェーダー用コンスタントバッファ(送信側)
	struct FadeCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		//0ならフェードイン、１ならフェードアウト
		float mode;
		//経過時間
		float time;
		DirectX::SimpleMath::Vector2 dummy;
	};


// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> FADE_INPUT_LAYOUT;
	// コンストラクタ
	FadeShader(const ShaderPath& pathes);
	// デストラクタ
	~FadeShader();
// 操作

//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:

};


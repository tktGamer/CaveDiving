/**
 * @file   FadeShader.h
 *
 * @brief  モデル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　22025/10/24
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Shader.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief モデルシェーダー
  */
class FadeShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct FadeCB
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		float mode;
		float time;
		DirectX::SimpleMath::Vector2 dummy;

	};

// データメンバの宣言 -----------------------------------------------
private:

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> FADE_INPUT_LAYOUT;
	// コンストラクタ
	FadeShader(const ShaderPath& pathes);

	// デストラクタ
	~FadeShader();


// 操作
public:
	
//　取得・設定
public:

//　内部操作
private:
	
};


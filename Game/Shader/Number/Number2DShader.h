/**
 * @file   Number2DShader.h
 *
 * @brief  モデル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　22025/12/08
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
class Number2DShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct Number2DCB
	{
		DirectX::SimpleMath::Vector2	windowSize;
		float AlphaData = 0;
		float dammy = 0;
		DirectX::SimpleMath::Vector4 numberColor;
	};

// データメンバの宣言 -----------------------------------------------
private:


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> NUMBER_2D_INPUT_LAYOUT;
	// コンストラクタ
	Number2DShader(const ShaderPath& pathes);

	// デストラクタ
	~Number2DShader();


// 操作
public:

//　取得・設定
public:

//　内部操作
private:
	
};


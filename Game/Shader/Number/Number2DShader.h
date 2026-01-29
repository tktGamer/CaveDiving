/**
 * @file   Number2DShader.h
 *
 * @brief  2D数字用シェーダーに関するヘッダファイル
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
  * @brief シェーダー
  */
class Number2DShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//2D数字用コンスタントバッファ
	struct Number2DCB
	{
		DirectX::SimpleMath::Vector2	windowSize;
		float alphaData = 0;
		//表示する数字
		int number = 0;
		//画像の横数
		int widthNumber;
		//画像の縦数
		int heightNumber;
		DirectX::SimpleMath::Vector2 dammy;
		//数字の色
		DirectX::SimpleMath::Vector4 numberColor;
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> NUMBER_2D_INPUT_LAYOUT;
	// コンストラクタ
	Number2DShader(const ShaderPath& pathes);

	// デストラクタ
	~Number2DShader();
// 操作

//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:
};


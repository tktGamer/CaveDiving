/**
 * @file   Animation2DShader.h
 *
 * @brief  2Dアニメーション用シェーダーに関するヘッダファイル
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
  * @brief 2Dアニメーション用シェーダー
  */
class Animation2DShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct Animation2DCB
	{
		//ウィンドウサイズ
		DirectX::SimpleMath::Vector2	windowSize = { 0.0f,0.0f };
		//透過
		float alphaData = 1.0f;
		//アニメーションする時間
		float animationTime = 0.0f;
		//経過時間
		float currentTime = 0.0f;
		//総枚数
		int frameCount = 0;
		//横の枚数
		int widthFrame = 0;
		//縦の枚数
		int heightFrame = 0;
	};

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> ANIMATION_2D_INPUT_LAYOUT;
	// コンストラクタ
	Animation2DShader(const ShaderPath& pathes);
	// デストラクタ
	~Animation2DShader();
// 操作

//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:

};


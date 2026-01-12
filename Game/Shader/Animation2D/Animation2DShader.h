/**
 * @file   Animation2DShader.h
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
class Animation2DShader : public Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct Animation2DCB
	{
		//ウィンドウサイズ
		DirectX::SimpleMath::Vector2	windowSize;
		//透過
		float alphaData;
		//アニメーションする時間
		float animationTime;
		//経過時間
		float currentTime;
		//総枚数
		int frameCount;
		//横の枚数
		int widthFrame;
		//縦の枚数
		int heightFrame;
	};

// データメンバの宣言 -----------------------------------------------
private:


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> ANIMATION_2D_INPUT_LAYOUT;
	// コンストラクタ
	Animation2DShader(const ShaderPath& pathes);

	// デストラクタ
	~Animation2DShader();


// 操作
public:

//　取得・設定
public:

//　内部操作
private:
	
};


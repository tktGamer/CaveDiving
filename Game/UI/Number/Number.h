/**
 * @file   Number.h
 *
 * @brief  数字に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/UI/UserInterface.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 数字
  */
class Number
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr int DIGIT_SIZE_X = 130;
	static constexpr int DIGIT_SIZE_Y = 130;

// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	//数字のテクスチャハンドルのポインタ
	ID3D11ShaderResourceView** m_pNumberTexture;
	int m_windowWidth, m_windowHeight;
	DirectX::SimpleMath::Vector2 m_textureSize;

	DirectX::SimpleMath::Vector2 m_scale;
	DirectX::SimpleMath::Vector2 m_baseScale;
	DirectX::SimpleMath::Vector2 m_position;

	UserInterface::ANCHOR m_anchor;

	float m_renderRatio;
	float m_renderRatioOffset;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Number(const std::string& texturepath,DirectX::SimpleMath::Vector2 textureSize);

	// デストラクタ
	~Number();


// 操作
public:
	void Initialize();

	void Update();

	void Draw(const int& number, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector2& scale, const DirectX::SimpleMath::Vector4& color);

	void Finalize();
//　取得・設定
public:

//　内部操作
private:

};


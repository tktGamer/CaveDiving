/**
 * @file   Number.h
 *
 * @brief  数字に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/30
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


// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//情報変更
	void ChangeNumber(const int& number, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector2& scale, const DirectX::SimpleMath::Vector4& color);
// コンストラクタ/デストラクタ
	// コンストラクタ
	Number(const std::string& texturepath,DirectX::SimpleMath::Vector2 textureSize);
	// デストラクタ
	~Number();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw(const int& number, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector2& scale, const DirectX::SimpleMath::Vector4& color);
	//終了
	void Finalize();

//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	//数字のテクスチャハンドルのポインタ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pNumberTexture;
	int m_windowWidth, m_windowHeight;
	DirectX::SimpleMath::Vector2 m_textureSize;

	int m_number;
	DirectX::SimpleMath::Vector2 m_scale;
	DirectX::SimpleMath::Vector2 m_position;
	DirectX::SimpleMath::Vector4 m_color;

	UserInterface::ANCHOR m_anchor;

	float m_renderRatio;
	float m_renderRatioOffset;

};


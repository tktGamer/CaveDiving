/**
 * @file   Gauge.h
 *
 * @brief  ゲージUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ゲージUI
  */
class Gauge
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//ゲージの参照数値の設定
	void SetValue(const int current, const int max);
//コンテキスト・デストラクタ
	//コンストラクタ
	Gauge();
	//デストラクタ
	~Gauge();
	//初期化
	void Initialize(int width, int height);
	//更新
	void Update();
	//描画
	void Render();

	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);


// データメンバの宣言 -----------------------------------------------
private:

	//ゲージ
	std::unique_ptr<UserInterface> m_gauge;
	//フレーム
	std::unique_ptr<UserInterface> m_frame;


	const wchar_t* m_baseTexturePath;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	//ゲージの参照する値
	int m_currentValue;
	int m_maxValue;
};

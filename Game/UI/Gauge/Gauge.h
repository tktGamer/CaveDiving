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
//非公開定数
private:	
	//アイコンテクスチャの位置
	static constexpr DirectX::SimpleMath::Vector2 OFFSET = {5.0f,-1.0f};
	//最小割合
	static constexpr float MIN_RATIO = 0.0f;
	//最大割合
	static constexpr float MAX_RATIO = 1.0f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//ゲージの参照数値の設定
	void SetValue(const int current, const int max);
//コンテキスト・デストラクタ
	//コンストラクタ
	Gauge(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor);
	//デストラクタ
	~Gauge();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();
// データメンバの宣言 -----------------------------------------------
private:

	//ゲージ
	std::unique_ptr<UserInterface> m_gauge;
	//フレーム
	std::unique_ptr<UserInterface> m_frame;
	//ゲージの参照する値
	int m_currentValue;
	int m_maxValue;
};

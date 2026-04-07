/**
 * @file   Particle.h
 *
 * @brief  パーティクルの基底に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/28
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクルの基底
  */
class Particle
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	//座標の取得
	const DirectX::SimpleMath::Vector3 GetPosition() const;
	//速度の設定
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity);
	//速度の取得
	const DirectX::SimpleMath::Vector3 GetVelocity() const;
	//加速度の設定
	void SetAccele(const DirectX::SimpleMath::Vector3& accele);
	//加速度の取得
	const DirectX::SimpleMath::Vector3 GetAccele() const;
	//現在の大きさの設定
	void SetScele(const DirectX::SimpleMath::Vector3& scale);
	//現在の大きさの取得
	const DirectX::SimpleMath::Vector3 GetNowScale() const;
	//初期の大きさの取得
	const DirectX::SimpleMath::Vector3 GetStartScale() const;
	//最終の大きさの取得
	const DirectX::SimpleMath::Vector3 GetEndScale() const;
	//残りの生存時間の設定
	void SetLife(const float& life);
	//残りの生存時間の取得
	const float GetLife() const;
	//初期生存時間の取得
	const float GetStartLife() const;
	//現在の色の設定
	void SetColor(const DirectX::SimpleMath::Color& color);
	//現在の色の取得
	const DirectX::SimpleMath::Color GetNowColor() const;
	//初期の色の取得
	const DirectX::SimpleMath::Color GetStartColor() const;
	//最終の色の取得
	const DirectX::SimpleMath::Color GetEndColor() const;
// コンストラクタ/デストラクタ
	//コンストラクタ
	Particle(const float& life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor, const DirectX::SimpleMath::Color& endColor);
	//デストラクタ
	virtual ~Particle();
// 操作
	//	更新
	virtual bool Update()=0;
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
	//	座標
	DirectX::SimpleMath::Vector3 m_position;
	//	速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//	加速度
	DirectX::SimpleMath::Vector3 m_accele;
	//	スケール
	DirectX::SimpleMath::Vector3 m_nowScale;
	DirectX::SimpleMath::Vector3 m_startScale;
	DirectX::SimpleMath::Vector3 m_endScale;
	//	生存時間
	float m_life;
	float m_startLife;
	//	カラー
	DirectX::SimpleMath::Color m_nowColor;
	DirectX::SimpleMath::Color m_startColor;
	DirectX::SimpleMath::Color m_endColor;
};

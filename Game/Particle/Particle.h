/**
 * @file   Particle.h
 *
 * @brief  パーティクルの基底に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2025/10/22
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



// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	Particle(const float& life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor, const DirectX::SimpleMath::Color& endColor);
		
	virtual ~Particle();
// 操作
public:

	//	更新
	virtual bool Update()=0;


//　取得・設定
public:
	//座標
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	const DirectX::SimpleMath::Vector3 GetPosition() const;

	//速度
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity);
	const DirectX::SimpleMath::Vector3 GetVelocity() const;

	//加速度
	void SetAccele(const DirectX::SimpleMath::Vector3& accele);
	const DirectX::SimpleMath::Vector3 GetAccele() const;

	//現在の大きさ
	void SetScele(const DirectX::SimpleMath::Vector3& scale);
	const DirectX::SimpleMath::Vector3 GetNowScale() const;
	//初期の大きさ
	const DirectX::SimpleMath::Vector3 GetStartScale() const;
	//最終の大きさ
	const DirectX::SimpleMath::Vector3 GetEndScale() const;

	//残りの生存時間
	void SetLife(const float& life);
	const float GetLife() const;
	//初期生存時間
	const float GetStartLife() const;

	//現在の色
	void SetColor(const DirectX::SimpleMath::Color& color);
	const DirectX::SimpleMath::Color GetNowColor() const;
	//初期の色
	const DirectX::SimpleMath::Color GetStartColor() const;
	//最終の色
	const DirectX::SimpleMath::Color GetEndColor() const;

//内部処理
private:

};

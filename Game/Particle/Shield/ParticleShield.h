/**
 * @file   ParticleShield.h
 *
 * @brief  盾パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/28
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Particle.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 盾パーティクル
  */
class ParticleShield : public Particle
{
// クラス定数の宣言 -------------------------------------------------
public:
	//回転スピード
	static constexpr float ROTATE_SPEED = 180.0f;
// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
	const DirectX::SimpleMath::Vector3& GetCenterPosition() const;
// コンストラクタ/デストラクタ
	//	コンストラクタ（初期設定）
	ParticleShield(
		const int& centerObjectID, 
		float life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor, const DirectX::SimpleMath::Color& endColor);
	//	デストラクタ
	~ParticleShield();

// 操作
public:
	//	更新
	bool Update() override;



// データメンバの宣言 -----------------------------------------------
private:
	//角度
	float m_angle = 0.0f;
	//円運動の中心オブジェクトのID
	const int m_centerObjectID;
};
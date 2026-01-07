/**
 * @file   ParticleShield.h
 *
 * @brief  盾パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2025/12/25
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
	//	変数


// データメンバの宣言 -----------------------------------------------
private:

	//	生存時間が経過した後の時間（消滅までの時間）
	float m_afterLife;

	DirectX::SimpleMath::Color m_afterColor;

	float m_angle = 0.0f;
	//円運動の中心座標
	const DirectX::SimpleMath::Vector3* m_centerPos;
	// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleShield(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor);
	//	デストラクタ
	~ParticleShield();

// 操作
public:
	//	更新
	bool Update() override;





};


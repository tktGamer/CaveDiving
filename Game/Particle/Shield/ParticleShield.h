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
#include <SimpleMath.h>

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


	float m_angle = 0.0f;
	//円運動の中心オブジェクトのID
	const int m_centerObjectID;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleShield(
		const int& centerObjectID, 
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


//取得・設定
	const DirectX::SimpleMath::Vector3& GetCenterPosition() const;

};


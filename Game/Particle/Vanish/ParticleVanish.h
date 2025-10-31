/**
 * @file   VanishParticle.h
 *
 * @brief  パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Particle.h"



// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleVanish : public Particle
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	変数


// データメンバの宣言 -----------------------------------------------
private:
	
	//	生存時間が経過した後の時間（消滅までの時間）
	float m_afterLife;

	DirectX::SimpleMath::Color m_afterColor;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleVanish(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor);
	//	デストラクタ
	~ParticleVanish();

// 操作
public:
	//	更新
	bool Update() override;

	


};


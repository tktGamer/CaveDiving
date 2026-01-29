/**
 * @file   ParticlePowerUp.h
 *
 * @brief  パワーアップパーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/27
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Particle.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パワーアップパーティクル
  */
class ParticlePowerUp : public Particle
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:

// コンストラクタ/デストラクタ
	//	コンストラクタ（初期設定）
	ParticlePowerUp(
		float life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor,const DirectX::SimpleMath::Color& endColor);
	//	デストラクタ
	~ParticlePowerUp();
// 操作
	//	更新
	bool Update() override;

// データメンバの宣言 -----------------------------------------------
private:

	//	生存時間が経過した後の時間（消滅までの時間）
	float m_afterLife;

	DirectX::SimpleMath::Color m_afterColor;
};


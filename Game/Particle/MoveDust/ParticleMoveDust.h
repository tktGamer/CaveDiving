/**
 * @file   ParticleMoveDust.h
 *
 * @brief  土埃パーティクルに関するヘッダファイル
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
  * @brief パーティクル
  */
class ParticleMoveDust : public Particle
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
// 取得・設定
public:
// コンストラクタ/デストラクタ
	//	コンストラクタ
	ParticleMoveDust(
		float life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor, const DirectX::SimpleMath::Color& endColor);
	//	デストラクタ
	~ParticleMoveDust();
// 操作
	//	更新
	bool Update() override;
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
};


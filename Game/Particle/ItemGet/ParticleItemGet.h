/**
 * @file   ParticleItemGet.h
 *
 * @brief  アイテム取得パーティクルに関するヘッダファイル
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
  * @brief アイテム取得パーティクル
  */
class ParticleItemGet : public Particle
{
// クラス定数の宣言 -------------------------------------------------
public:
	//消去する距離
	static constexpr float DELETE_DISTANCE = 1.5f;
// メンバ関数の宣言 -------------------------------------------------
//　操作
public:
// コンストラクタ/デストラクタ
	//	コンストラクタ
	ParticleItemGet(
		const DirectX::SimpleMath::Vector3& targetPos,
		float life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor,const DirectX::SimpleMath::Color& endColor);
	//	デストラクタ
	~ParticleItemGet();
// 操作
	//	更新
	bool Update() override;

// データメンバの宣言 -----------------------------------------------
private:
	//目標位置
	const DirectX::SimpleMath::Vector3* m_targetPos;
	//速度
	float m_speed;
};


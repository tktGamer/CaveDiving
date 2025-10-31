/**
 * @file   ParticleItemGet.h
 *
 * @brief  アイテム取得パーティクルに関するヘッダファイル
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
  * @brief アイテム取得パーティクル
  */
class ParticleItemGet : public Particle
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	変数


// データメンバの宣言 -----------------------------------------------
private:
	const DirectX::SimpleMath::Vector3* m_targetPos;

	float m_speed;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleItemGet(
		const DirectX::SimpleMath::Vector3& targetPos,
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor);
	//	デストラクタ
	~ParticleItemGet();

// 操作
public:
	//	更新
	bool Update() override;

	


};


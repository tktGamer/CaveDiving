/**
 * @file   ParticlePowerUpControl.h
 *
 * @brief  パワーアップパーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2025/12/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

#include"../ParticleControl.h"
#include"../PowerUp/ParticlePowerUp.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticlePowerUpControl : public ParticleControl
{
	// クラス定数の宣言 -------------------------------------------------
private:
	

public:

// データメンバの宣言 -----------------------------------------------
private:


	const DirectX::SimpleMath::Vector3* m_centerPos;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticlePowerUpControl(const std::string& texturePath);
	~ParticlePowerUpControl();
	// 操作
public:


	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);

	void RequestParticlePowerUp(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		DirectX::SimpleMath::Color color//パーティクルの発生位置
		);
	
	void Reset();
//　取得・設定
public:

private:

};

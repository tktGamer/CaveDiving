/**
 * @file   ParticleShieldControl.h
 *
 * @brief  盾パーティクル管理に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2025/12/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

#include"../ParticleControl.h"
#include"../Shield/ParticleShield.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 盾パーティクル管理
  */
class ParticleShieldControl : public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
private:


public:

// データメンバの宣言 -----------------------------------------------
private:

	//円運動の中心座標
	const DirectX::SimpleMath::Vector3* m_centerPos;
	//無敵回数

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticleShieldControl(const wchar_t* texturePath);
	~ParticleShieldControl();
	// 操作
public:


	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);

	void RequestParticleShield(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
		);
	
	void Reset();
//　取得・設定
public:

private:

};

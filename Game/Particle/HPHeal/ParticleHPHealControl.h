/**
 * @file   ParticleHPHealControl.h
 *
 * @brief  HP回復パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2025/12/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

#include"../ParticleControl.h"
#include"../HPHeal/ParticleHPHeal.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleHPHealControl : public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
private:
	static constexpr int HPHEAL_PARTICLE_NUM = 4; // パーティクルの数
	//生成したパーティクルの進む方向
	static constexpr DirectX::SimpleMath::Vector3 HPHEAL_PARTICLE_POSITION[HPHEAL_PARTICLE_NUM] =
	{
		{  1.0f, -1.0f, -2.0f }, 
		{ -1.0f, -1.0f,  0.0f }, 
		{  1.5f, -0.5f, -1.0f }, 
		{  0.5f, -0.5f,  1.0f }, 
	};


public:

// データメンバの宣言 -----------------------------------------------
private:


	const DirectX::SimpleMath::Vector3* m_centerPos;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticleHPHealControl(const std::string& texturePath);
	~ParticleHPHealControl();
// 操作
public:


	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);

	void RequestParticleHPHeal(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
		);
	
	void Reset();
//　取得・設定
public:

private:

};

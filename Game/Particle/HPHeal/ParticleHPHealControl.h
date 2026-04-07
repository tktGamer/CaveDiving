/**
 * @file   ParticleHPHealControl.h
 *
 * @brief  HP回復パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/26
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
public:
//非公開定数
private:
	// パーティクルの数
	static constexpr int HPHEAL_PARTICLE_NUM = 8;
	//生成したパーティクルの進む方向
	static constexpr DirectX::SimpleMath::Vector3 HPHEAL_PARTICLE_POSITION[HPHEAL_PARTICLE_NUM] =
	{
		{  1.0f, -1.0f, -2.0f }, 
		{ -1.0f, -1.0f,  0.0f }, 
		{  1.5f, -0.5f, -1.0f }, 
		{  0.5f, -0.5f,  1.0f }, 
		{  0.5f, -1.0f, -2.5f }, 
		{ -1.0f, -1.0f,  0.0f }, 
		{  1.5f,  0.5f, -1.0f }, 
		{  1.5f, -1.5f,  1.0f }, 
	};
	//パーティクルの速度
	static constexpr DirectX::SimpleMath::Vector3 HPHEAL_PARTICLE_VELOCITY = { 0.0f,9.0f,0.0f };

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//　コンストラクタ
	ParticleHPHealControl(const wchar_t* texturePath);
	//　デストラクタ
	~ParticleHPHealControl();
// 操作
	//更新
	void Update();
	//描画
	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);
	//パーティクル生成要求
	void RequestParticleHPHeal(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
		);
	//リセット
	void Reset();
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
	//中心位置
	const DirectX::SimpleMath::Vector3* m_centerPos;
};

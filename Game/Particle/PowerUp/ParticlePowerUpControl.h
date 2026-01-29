/**
 * @file   ParticlePowerUpControl.h
 *
 * @brief  パワーアップパーティクル管理に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/27
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
public:
//非公開定数
private:
	//一度のパーティクル生成数
	static constexpr int PARTICLE_GENERATE_NUM = 6;
	//パーティクルの生存時間
	static constexpr float PARTICLE_LIFE = 0.35f;
	//速度
	static constexpr DirectX::SimpleMath::Vector3 PARTICLE_VELOCITY = { 0.0f,10.0f,0.0f };
	//
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//コンストラクタ
	ParticlePowerUpControl(const wchar_t* texturePath);
	//デストラクタ
	~ParticlePowerUpControl();
// 操作
	//更新
	void Update();
	//描画
	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);
	//パワーアップパーティクル要求
	void RequestParticlePowerUp(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		const DirectX::SimpleMath::Color& color//パーティクルの色
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

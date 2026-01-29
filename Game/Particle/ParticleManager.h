/**
 * @file   ParticleManager.h
 *
 * @brief  パーティクルの管理クラスに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付 2026/01/28
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include<unordered_map>
#include"../Particle/Vanish/ParticleVanishControl.h"
#include"../Particle/PowerUp/ParticlePowerUpControl.h"
#include"../Particle/MoveDust/ParticleMoveDustControl.h"
#include"../Particle/ItemGet/ParticleItemGetControl.h"
#include"../Particle/Damage/ParticleDamageControl.h"
#include"../Particle/HPHeal/ParticleHPHealControl.h"
#include"../Particle/Shield/ParticleShieldControl.h"
// クラスの宣言 ===============================================================
class Camera;
// クラスの定義 ===============================================================
/**
  * @brief パーティクル管理クラス
  */
class ParticleManager
{
// クラス定数の宣言 -------------------------------------------------
public:
	//パーティクルの種類
	enum ParticleType
	{
		Vanish = 0,
		PowerUp,
		MoveDust,
		ItemGet,
		Daamge,
		HPHeal,
		Shield,
		Num
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//カメラオブジェクトの設定
	void SetCamera(const Camera* pCamera);
//デストラクタ
	//デストラクタ
	~ParticleManager();
// 操作
	// ParticleManagerクラスのインスタンスを取得する
	static ParticleManager* const GetInstance();

	//更新
	void Update();
	//描画
	void Render();
	//リセット
	void Reset();

	//敵消滅パーティクル生成
	void RequestVanishParticle(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
	);
	//パワーアップパーティクル生成
	void RequestPowerUpParticle(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		const DirectX::SimpleMath::Color& color//パーティクルの色
	);
	//移動時土埃パーティクル生成
	void RequestMoveDustParticle(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
	);
	//アイテムゲットパーティクル生成
	void RequestItemGetParticle(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		const DirectX::SimpleMath::Vector3& targetPos,//向かっていくオブジェクト位置
		const DirectX::SimpleMath::Color& color //パーティクルの色
	);
	//ダメージパーティクル生成
	void RequestDamageParticle(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		const DirectX::SimpleMath::Vector3& randomRange, 
		int damage
	);
	//HP回復パーティクル生成
	void RequestHPHealParticle(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
	);
	//盾パーティクル生成
	void RequestShieldParticle(
		const int& objectID
		);
	void DeleteShieldParticle(
		const int& objectID
		);

//内部処理
private:
// コンストラクタ
	//コントラクタ
	ParticleManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const ParticleManager&) = delete;
	// インスタンスをムーブすることを禁止する
	ParticleManager& operator= (ParticleManager&&) = delete;
	// コピーコンストラクタは禁止する
	ParticleManager(const ParticleManager&) = delete;
	// ムーブコンストラクタは禁止する
	ParticleManager(ParticleManager&&) = delete;

// データメンバの宣言 -----------------------------------------------
private:
	// ParticleManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<ParticleManager> s_particleManager;
	//パーティクルコントロールクラス配列
	std::unordered_map<ParticleType, std::unique_ptr<ParticleControl>> m_particleCotrolers;
	//カメラクラスポインタ
	const Camera* m_pCamera;

	//消滅パーティクルの管理クラス
	std::unique_ptr<ParticleVanishControl> m_particleVanishControl;
	//パワーアップパーティクルの管理クラス
	std::unique_ptr<ParticlePowerUpControl> m_particlePowerUpControl;
	//移動時の土埃パーティクルの管理クラス
	std::unique_ptr<ParticleMoveDustControl> m_particleMoveDustControl;
	//アイテムゲットパーティクルの管理クラス
	std::unique_ptr<ParticleItemGetControl> m_particleItemGetControl;
	//ダメージパーティクルの管理クラス
	std::unique_ptr<ParticleDamageControl> m_particleDamageControl;
	//HP回復パーティクルの管理クラス
	std::unique_ptr<ParticleHPHealControl> m_particleHPHealControl;
	//盾パーティクルの管理クラス
	std::unique_ptr<ParticleShieldControl> m_particleShieldControl;
};
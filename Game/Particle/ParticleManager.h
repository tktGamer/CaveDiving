/**
 * @file   ParticleManager.h
 *
 * @brief  パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付 2025/10/23
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

#include"../Particle/Vanish/ParticleVanishControl.h"
#include"../Particle/PowerUp/ParticlePowerUpControl.h"
#include"../Particle/MoveDust/ParticleMoveDustControl.h"
#include"../Particle/ItemGet/ParticleItemGetControl.h"
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
	enum ParticleType
	{
		Vanish = 0,
		PowerUp,
		MoveDust,
		ItemGet,
		Hit,
		Num
	};
// データメンバの宣言 -----------------------------------------------
private:
	// ParticleManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<ParticleManager> s_particleManager;

	//カメラクラスポインタ
	Camera* m_pCamera;
	
	//消滅パーティクルの管理クラス
	std::unique_ptr<ParticleVanishControl> m_particleVanishControl;
	//パワーアップパーティクルの管理クラス
	std::unique_ptr<ParticlePowerUpControl> m_particlePowerUpControl;
	//移動時の土埃パーティクルの管理クラス
	std::unique_ptr<ParticleMoveDustControl> m_particleMoveDustControl;
	//アイテムゲットパーティクルの管理クラス
	std::unique_ptr<ParticleItemGetControl> m_particleItemGetControl;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
private:

	ParticleManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const ParticleManager&) = delete;
	// インスタンスをムーブすることを禁止する
	ParticleManager& operator= (ParticleManager&&) = delete;
	// コピーコンストラクタは禁止する
	ParticleManager(const ParticleManager&) = delete;
	// ムーブコンストラクタは禁止する
	ParticleManager(ParticleManager&&) = delete;

// 操作
public:
	~ParticleManager();
	// ParticleManagerクラスのインスタンスを取得する
	static ParticleManager* const GetInstance();

	//更新
	void Update();
	//描画
	void Render();

	//リセット
	void Reset();

//　取得・設定
public:
	//敵消滅パーティクル生成
	void RequestVanishParticle(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
	);
	//パワーアップパーティクル生成
	void RequestPowerUpParticle(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		DirectX::SimpleMath::Color color//パーティクルの色
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

	void SetCamera(Camera* pCamera);
private:

	
};

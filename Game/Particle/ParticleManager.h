/**
 * @file   ParticleManager.h
 *
 * @brief  パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

#include"../Particle/Vanish/ParticleVanishControl.h"
#include"../Particle/PowerUp/ParticlePowerUpControl.h"

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
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticleManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const ParticleManager&) = delete;
	// インスタンスをムーブすることを禁止する
	ParticleManager& operator= (ParticleManager&&) = delete;
	// コピーコンストラクタは禁止する
	ParticleManager(const ParticleManager&) = delete;
	// ムーブコンストラクタは禁止する
	ParticleManager(ParticleManager&&) = delete;

	~ParticleManager();
// 操作
public:
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
	//パーティクル生成
	void RequestParticle(
		ParticleType type,//パーティクルの種類
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		DirectX::SimpleMath::Color color//パーティクルの発生位置
	);

	void SetCamera(Camera* pCamera);
private:

	
};

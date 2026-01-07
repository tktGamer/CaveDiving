/**
 * @file   ParticleManager.cpp
 *
 * @brief  パーティクルの管理クラスに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/10
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleManager.h"
#include"Game/Object/Camera.h"
#include"../ResourcePath.h"
std::unique_ptr<ParticleManager> ParticleManager::s_particleManager = nullptr;

/**
 * @brief インスタンスの取得
 *
 * @param[in] なし
 *
 * @return 　パーティクルマネージャーのポインタ
 */
ParticleManager* const ParticleManager::GetInstance()
{

	if (s_particleManager == nullptr)
	{
		//ParticleManagerオブジェクトを生成し、そのポインタをs_resourceManagerに格納する
		s_particleManager.reset(new ParticleManager());
	}
	return s_particleManager.get();
}


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ParticleManager::ParticleManager()
	:m_pCamera{nullptr}
	
{
	//それぞれのパーティクル管理クラスの生成
	m_particleVanishControl   = std::make_unique<ParticleVanishControl>  (ResourcePath::TEXTURE::PARTICLE::VANISH);
	m_particlePowerUpControl  = std::make_unique<ParticlePowerUpControl> (ResourcePath::TEXTURE::PARTICLE::POWER_UP);
	m_particleMoveDustControl = std::make_unique<ParticleMoveDustControl>(ResourcePath::TEXTURE::PARTICLE::MOVE_DUST);
	m_particleItemGetControl  = std::make_unique<ParticleItemGetControl> (ResourcePath::TEXTURE::PARTICLE::ITEM_GET);
	m_particleDamageControl   = std::make_unique<ParticleDamageControl>  (ResourcePath::TEXTURE::PARTICLE::NUMBER);
	m_particleHPHealControl   = std::make_unique<ParticleHPHealControl>  (ResourcePath::TEXTURE::PARTICLE::HP_HEAL);
	m_particleShieldControl   = std::make_unique<ParticleShieldControl>  (ResourcePath::TEXTURE::PARTICLE::SHIELD);
}

/**
 * @brief デストラクタ
 */
ParticleManager::~ParticleManager()
{
}



/**
 * @brief 更新
 *
 * @param[in]  なし
 * 
 * @return なし
 */
void ParticleManager::Update()
{
	m_particleVanishControl->Update();
	m_particleMoveDustControl->Update();
	m_particlePowerUpControl->Update();
	m_particleItemGetControl->Update();
	m_particleDamageControl->Update();
	m_particleHPHealControl->Update();
	m_particleShieldControl->Update();
}


/**
 * @brief 描画
 *
 * @param[in]  なし
 * 
 * @return なし
 */
void ParticleManager::Render()
{
	//カメラの情報を取得
	const DirectX::SimpleMath::Vector3& target = m_pCamera->GetTargetPos();
	const DirectX::SimpleMath::Vector3 eye     = m_pCamera->GetEyePos();
	const DirectX::SimpleMath::Vector3& up     = m_pCamera->GetUP();

	m_particleVanishControl->Render(target,eye,up);
	m_particlePowerUpControl->Render(target,eye,up);
	m_particleMoveDustControl->Render(target, eye, up);
	m_particleItemGetControl->Render(target, eye, up);
	m_particleDamageControl->Render(target, eye, up);
	m_particleHPHealControl->Render(target, eye, up);
	m_particleShieldControl->Render(target, eye, up);
}

/**
 * @brief リセット
 *
 * @param[in]  なし
 * 
 * @return なし
 */
void ParticleManager::Reset()
{
	m_particleVanishControl->Reset();
	m_particlePowerUpControl->Reset();
	m_particleMoveDustControl->Reset();
	m_particleItemGetControl->Reset();
	m_particleDamageControl->Reset();
	m_particleHPHealControl->Reset();
	m_particleShieldControl->Reset();
}



/**
 * @brief 敵消滅パーティクル生成要求
 *
 * @param[in]  pos  生成位置
 *
 * @return なし
 */
void ParticleManager::RequestVanishParticle(const DirectX::SimpleMath::Vector3& pos)
{
	m_particleVanishControl->RequestVanishParticle(pos);

}

/**
 * @brief パワーアップパーティクル生成要求
 *
 * @param[in]  pos    生成位置
 * @param[in]  color  色
 *
 * @return なし
 */
void ParticleManager::RequestPowerUpParticle(const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Color& color)
{
	m_particlePowerUpControl->RequestParticlePowerUp(pos, color);

}

/**
 * @brief 移動時土埃パーティクル生成要求
 *
 * @param[in]  pos  生成位置
 *
 * @return なし
 */
void ParticleManager::RequestMoveDustParticle(const DirectX::SimpleMath::Vector3& pos)
{
	m_particleMoveDustControl->RequestMoveDustParticle(pos);
}

/**
 * @brief アイテムゲットパーティクル生成要求
 *
 * @param[in]  pos        生成位置
 * @param[in]  targetPos  目標位置
 * @param[in]  color      色
 *
 * @return なし
 */
void ParticleManager::RequestItemGetParticle(const DirectX::SimpleMath::Vector3& pos,const DirectX::SimpleMath::Vector3& targetPos,const DirectX::SimpleMath::Color& color)
{
	m_particleItemGetControl->RequestItemGetParticle(pos,targetPos,color);

}


/**
 * @brief ダメージパーティクル生成要求
 *
 * @param[in]  pos 生成位置
 * @param[in]  randomRange
 * @param[in]  damage
 *
 * @return なし
 */
void ParticleManager::RequestDamageParticle(const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& randomRange,int damage)
{
	m_particleDamageControl->RequestParticleDamage(pos, randomRange, damage);
}


/**
 * @brief HP回復パーティクル生成要求
 *
 * @param[in]  pos 生成位置
 *
 * @return なし
 */
void ParticleManager::RequestHPHealParticle(const DirectX::SimpleMath::Vector3& pos)
{
	m_particleHPHealControl->RequestParticleHPHeal(pos);
}

/**
 * @brief 盾パーティクル生成要求
 *
 * @param[in]  pos 生成位置
 *
 * @return なし
 */
void ParticleManager::RequestShieldParticle(const DirectX::SimpleMath::Vector3& pos)
{
	m_particleShieldControl->RequestParticleShield(pos);
}


/**
 * @brief カメラポインタ設定
 *
 * @param[in]  カメラクラスのポインタ
 *
 * @return なし
 */
void ParticleManager::SetCamera(const Camera* pCamera)
{
	m_pCamera = pCamera;
}

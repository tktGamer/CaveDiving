//--------------------------------------------------------------------------------------
// File: ParticleManager.cpp
//
// パーティクルクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "ParticleManager.h"
#include"Game/Object/Camera.h"

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
	m_particleVanishControl = std::make_unique<ParticleVanishControl>("vanish.png");
	m_particlePowerUpControl = std::make_unique<ParticlePowerUpControl>("powerup.png");
}

/**
 * @brief デストラクタ
 */
ParticleManager::~ParticleManager()
{
}


/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">Game等からStepTimerを受け取る</param>
void ParticleManager::Update()
{
	m_particleVanishControl->Update();

	m_particlePowerUpControl->Update();
}


/// <summary>
/// 描画関数
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void ParticleManager::Render()
{
	const DirectX::SimpleMath::Vector3& target = m_pCamera->GetTargetPos();
	const DirectX::SimpleMath::Vector3& eye = m_pCamera->GetEyePos();
	const DirectX::SimpleMath::Vector3& up = m_pCamera->GetUP();

	m_particleVanishControl->Render(target,eye,up);
	m_particlePowerUpControl->Render(target,eye,up);
}

void ParticleManager::Reset()
{
	m_particleVanishControl->Reset();
	m_particlePowerUpControl->Reset();
}

void ParticleManager::RequestParticle(ParticleType type,const DirectX::SimpleMath::Vector3& pos, DirectX::SimpleMath::Color color)
{
	switch (type)
	{
	case ParticleManager::Vanish:
		m_particleVanishControl->RequestVanishParticle(pos);
		break;
	case ParticleManager::PowerUp:
		m_particlePowerUpControl->RequestParticlePowerUp(pos,color);
		break;
	case ParticleManager::Hit:
		break;
	case ParticleManager::Num:
		break;
	default:
		break;
	}
}

void ParticleManager::SetCamera(Camera* pCamera)
{
	m_pCamera = pCamera;
}


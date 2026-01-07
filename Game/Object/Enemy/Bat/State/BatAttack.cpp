/**
 * @file   BatAttack.cpp
 *
 * @brief  コウモリの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/12/03
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Bat/State/BatAttack.h"
#include "Game/Object/Enemy/Bat/Bat.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 * @param[in] pRightWing コウモリ右羽のポインタ
 * @param[in] pLeftWing  コウモリ左羽のポインタ
 */
BatAttack::BatAttack(Bat* bat, Wing* pRightWing, Wing* pLeftWing)
	:m_bat(bat)
{

	m_attackMotion = std::make_unique<BatAttackMotion>(bat,pRightWing,pLeftWing);

	m_attackSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::BAT_ATTACK),true);
}
/**
 * @brief デストラクタ
 */
BatAttack::~BatAttack()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Initialize()
{
	PreUpdate();
}

/**
 * @brief 事前処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::PreUpdate()
{
	m_attackSound->SetVolume(Sound::VOLUME_MAX);
	m_attackSound->Play(false);
	m_attackMotion->Initialize();

	m_bat->SetMotionAttackRate(m_attackMotion->GetAttackPowerModifier());
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime フレーム間時間
 *
 * @return なし
 */
void BatAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	DirectX::SimpleMath::Vector3 velocity = m_bat->GetVelocity();


	velocity.y += FALL_SPEED * elapsedTime;

	//モーションが終了したら
	if (m_attackMotion->Update()) 
	{
		//待機状態にする
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::MessageID::IDLING);
	}

	m_bat->SetVelocity(velocity);

	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());


	//3Dオーディオ　　ーー未完ーー
	DirectX::AudioEmitter emitter{};
	emitter.SetPosition(m_bat->GetCurrentPosition());
	emitter.SetOrientationFromQuaternion(m_bat->GetCurrentQuaternion());
	m_attackSound->Update(emitter);

}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::PostUpdate()
{
	m_attackSound->Stop();
	m_attackMotion->Reset();
	m_bat->SetMotionAttackRate(Bat::CONTACT_DAMAGE_MODIFIRE);

}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Render()
{

#ifdef _DEBUG
#endif // DEBUG

}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BatAttack::Finalize()
{
}


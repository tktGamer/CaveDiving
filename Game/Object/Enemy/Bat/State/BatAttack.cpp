/**
 * @file   BatAttack.cpp
 *
 * @brief  コウモリの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"Game/Motion/BatMotion/BatAttackMotion.h"
#include "Game/Object/Enemy/Bat/State/BatAttack.h"
#include "Game/Object/Enemy/Bat/Bat.h"
#include"Game/Common/Sound.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] bat コウモリのポインタ
 * @param[in] pRightWing コウモリ右羽のポインタ
 * @param[in] pLeftWing  コウモリ左羽のポインタ
 */
BatAttack::BatAttack(Bat* bat, Wing* pRightWing, Wing* pLeftWing)
	:
	m_bat{bat},
	m_attackMotion{},
	m_attackSound{}
{
	//モーション生成
	m_attackMotion = std::make_unique<BatAttackMotion>(bat,pRightWing,pLeftWing);
	//効果音生成
	m_attackSound = std::make_unique<Sound>(ResourceManager::GetInstance()->RequestSound(ResourcePath::SOUND::BAT_ATTACK));
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
	//音再生
	m_attackSound->SetVolume(Sound::VOLUME_MAX);
	m_attackSound->Play(false);
	//モーション初期化
	m_attackMotion->Initialize();
	//攻撃力補正値設定
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
	//モーションが終了したら
	if (m_attackMotion->Update()) 
	{
		//待機状態にする
		Messenger::GetInstance()->Notify(m_bat->GetObjectNumber(), Message::MessageID::IDLING);
	}
	//速度
	DirectX::SimpleMath::Vector3 velocity = m_bat->GetVelocity();
	//落下
	velocity.y += FALL_SPEED * elapsedTime;
	//速度設定
	m_bat->SetVelocity(velocity);
	//座標更新
	m_bat->SetPosition(m_bat->GetPosition() + m_bat->GetVelocity());
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
	//音停止
	m_attackSound->Stop();
	//モーションリセット
	m_attackMotion->Reset();
	//攻撃力補正設定
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
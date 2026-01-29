/**
 * @file   GolemAttack.cpp
 *
 * @brief  ゴーレムの攻撃状態に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Object/Enemy/Golem/State/GolemAttack.h"
#include "Game/Object/Enemy/Golem/Golem.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] golem ゴーレムのポインタ
 * @param[in] pRightGolemHand ゴーレムの右手のポインタ
 * @param[in] pLeftGolemHand ゴーレムの左手のポインタ
 */
GolemAttack::GolemAttack(Golem* golem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand)
	:
	m_golem{golem},
	m_pRightHand{ pRightGolemHand },
	m_pLeftHand{ pLeftGolemHand },
	m_attackMotion{}
{
	//モーションを設定
	m_attackMotion = std::make_unique<GolemPunchMotion>(golem, pRightGolemHand, pLeftGolemHand);
}
/**
 * @brief デストラクタ
 */
GolemAttack::~GolemAttack()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttack::Initialize()
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
void GolemAttack::PreUpdate()
{
	//モーション決定
	DecideMotion();
	//モーション初期化
	m_attackMotion->Initialize();
	//攻撃力補正を設定
	m_golem->SetMotionAttackRate(m_attackMotion->GetAttackPowerModifier());
}

/**
 * @brief 更新処理
 *
 * @param[in] elapsedTime
 *
 * @return なし
 */
void GolemAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	DirectX::SimpleMath::Vector3 velocity = m_golem->GetVelocity();

	//モーションが終了したら状態を遷移
	if(m_attackMotion->Update()) 
	{
		//待機状態へ
		Messenger::GetInstance()->Notify(m_golem->GetObjectNumber(), Message::MessageID::IDLING);
	}

	//重力
	velocity.y += World::GRAVITY * elapsedTime;
	m_golem->SetVelocity(velocity);
}

/**
 * @brief 事後更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttack::PostUpdate()
{
	//モーションをリセット
	m_attackMotion->Reset();
	//経過時間リセット
	m_golem->ResetFrameCount();
	//攻撃力補正を設定
	m_golem->SetMotionAttackRate(Golem::CONTACT_DAMAGE_MODIFIRE);

}

/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GolemAttack::Render()
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
void GolemAttack::Finalize()
{
}

/**
 * @brief 攻撃のモーションを決定する
 *
 * @param[in] なし
 *
 * @return なし
 */
void  GolemAttack::DecideMotion()
{
	switch (m_golem->GetAttackMessage())
	{
	case Message::AttackMesssage::ATTACKTYPE_ONE:
		m_attackMotion = std::make_unique<GolemPunchMotion>(m_golem, m_pRightHand, m_pLeftHand);
		break;
	case Message::AttackMesssage::ATTACKTYPE_TWO:
		m_attackMotion = std::make_unique<GolemSlammedDownMotion>(m_golem, m_pRightHand, m_pLeftHand);

		break;
	}
}
